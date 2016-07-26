#include "stdafx.h"
#include "DlgFlags.h"
#include "Valid.h"
#include "Dialog_box.h"
#include "DlgFlagsIssue.h"
#include "Accumulator.h"

DlgFlags::DlgFlags(const Dialog_box &dlg) :
	dialog(dlg)
{
}

unique_ptr<Issue> DlgFlags::createIssue(const vector < pair<DlgFlags::action, DlgFlags::flag> > &suggestions) {
	return make_unique <DlgFlagsIssue>(suggestions);
}

void DlgFlags::validate(Accumulator &issueAccumulator) {
	
	vector < pair<DlgFlags::action, DlgFlags::flag> > suggestionsForFix;

	// MODALFRAME + POPUP + CAPTION + WS_SYSMENU
	if (dialog.hasFlagDS_MODALFRAME() && dialog.hasFlagWS_POPUP() && 
		dialog.hasFlagWS_CAPTION() && dialog.hasFlagWS_SYSMENU()) {

		// remove DS_MODALFRAME
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_DS_MODALFRAME));

		// add WS_THICKFRAME if not defined
		if (!dialog.hasFlagWS_THICKFRAME()) {
			suggestionsForFix.push_back(make_pair(action::ADD, flag::FLAG_WS_THICKFRAME));
		}

		nrIssuesDlgFlags++;
	}
	// POPUP + SYSMENU - CAPTION => CHILD
	else if (dialog.hasFlagWS_POPUP() && dialog.hasFlagWS_SYSMENU() && !dialog.hasFlagWS_CAPTION()) {
		// remove WS_POPMENU and WS_SYSMENU
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_POPUP));
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_SYSMENU));

		// add WS_CHILD
		suggestionsForFix.push_back(make_pair(action::ADD, flag::FLAG_WS_CHILD));

		nrIssuesDlgFlags++;
	}

	// push the issues
	if (!suggestionsForFix.empty()) {
		issueAccumulator.push_issue(createIssue(suggestionsForFix));
	}
}