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
	
	// WS_CHILD + WS_SYSMENU ( + WS_CAPTION + WS_THICKFRAME / DS_MODALFRAME)
	if (dialog.hasFlaWS_CHILD() && dialog.hasFlagWS_SYSMENU()) {
		// remove WS_SYSMENU
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_SYSMENU));

		// remove WS_CAPTION
		if (dialog.hasFlagWS_CAPTION()) {
			suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_CAPTION));
		}

		// remove WS_THICKFRAME and add DS_MODALFRAME instead
		if (dialog.hasFlagWS_THICKFRAME()) {
			suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_THICKFRAME));
			suggestionsForFix.push_back(make_pair(action::ADD,	  flag::FLAG_DS_MODALFRAME));
		}
	}
	// MODALFRAME + POPUP + CAPTION + WS_SYSMENU
	else if (dialog.hasFlagDS_MODALFRAME() && dialog.hasFlagWS_POPUP() && 
		dialog.hasFlagWS_CAPTION() && dialog.hasFlagWS_SYSMENU()) {

		// remove DS_MODALFRAME
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_DS_MODALFRAME));

		// add WS_THICKFRAME if not defined
		if (!dialog.hasFlagWS_THICKFRAME()) {
			suggestionsForFix.push_back(make_pair(action::ADD, flag::FLAG_WS_THICKFRAME));
		}
	}
	// POPUP + SYSMENU - CAPTION => CHILD
	else if (dialog.hasFlagWS_POPUP() && dialog.hasFlagWS_SYSMENU() && !dialog.hasFlagWS_CAPTION()) {
		// remove WS_POPMENU and WS_SYSMENU
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_POPUP));
		suggestionsForFix.push_back(make_pair(action::REMOVE, flag::FLAG_WS_SYSMENU));

		// add WS_CHILD
		suggestionsForFix.push_back(make_pair(action::ADD, flag::FLAG_WS_CHILD));
	}

	// push the issues
	if (!suggestionsForFix.empty()) {
		issueAccumulator.push_issue(createIssue(suggestionsForFix));

		// increment the number of issues
		nrIssuesDlgFlags++;
	}
}