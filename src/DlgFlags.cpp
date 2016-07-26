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

unique_ptr<Issue> DlgFlags::createIssue(const flag &chosenFlag, const action &chosenAction) {
	return make_unique <DlgFlagsIssue>(chosenFlag, chosenAction);
}

void DlgFlags::validate(Accumulator &issueAccumulator) {
	
	// MODALFRAME + POPUP + CAPTION + WS_SYSMENU
	if (dialog.hasFlagDS_MODALFRAME() && dialog.hasFlagWS_POPUP() && 
		dialog.hasFlagWS_CAPTION() && dialog.hasFlagWS_SYSMENU()) {

		// remove DS_MODALFRAME
		issueAccumulator.push_issue(createIssue(flag::FLAG_DS_MODALFRAME, action::REMOVE));

		// add WS_THICKFRAME if not defined
		if (!dialog.hasFlagWS_THICKFRAME()) {
			issueAccumulator.push_issue(createIssue(flag::FLAG_WS_THICKFRAME, action::ADD));
		}

		nrIssuesDlgFlags++;
	}
	// POPUP + SYSMENU - CAPTION => CHILD
	else if (dialog.hasFlagWS_POPUP() && dialog.hasFlagWS_SYSMENU() && !dialog.hasFlagWS_CAPTION()) {
		// remove WS_POPMENU and WS_SYSMENU
		issueAccumulator.push_issue(createIssue(flag::FLAG_WS_POPUP	 , action::REMOVE));
		issueAccumulator.push_issue(createIssue(flag::FLAG_WS_SYSMENU, action::REMOVE));

		// add WS_CHILD
		issueAccumulator.push_issue(createIssue(flag::FLAG_WS_CHILD  , action::ADD));

		nrIssuesDlgFlags++;
	}
}