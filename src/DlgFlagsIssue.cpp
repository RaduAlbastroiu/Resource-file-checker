#include "stdafx.h"
#include "widget.h"
#include "Issue.h"
#include "DlgFlags.h"
#include "DlgFlagsIssue.h"

DlgFlagsIssue::DlgFlagsIssue(DlgFlags::flag chosenFlag, DlgFlags::action chosenAction)
{
	flag	= flagToWstring(chosenFlag);
	action	= actionToWstring(chosenAction);
}

vector<wstring> DlgFlagsIssue::Create_message() {

	vector<wstring> outputText;

	outputText.push_back(action + L" flag " + flag + L"\n\n");

	return outputText;
}

wstring DlgFlagsIssue::actionToWstring(DlgFlags::action chosenAction) {
	return chosenAction == DlgFlags::action::ADD ? L"Add" : L"Remove";
}

wstring DlgFlagsIssue::flagToWstring(DlgFlags::flag chosenFlag) {
	switch (chosenFlag)
	{
		case DlgFlags::flag::FLAG_WS_CHILD:
			return L"WS_CHILD";

		case DlgFlags::flag::FLAG_WS_SYSMENU:
			return L"WS_SYSMENU";

		case DlgFlags::flag::FLAG_WS_CAPTION:
			return L"WS_CAPTION";

		case DlgFlags::flag::FLAG_WS_BORDER:
			return L"WS_BORDER";

		case DlgFlags::flag::FLAG_WS_POPUP:
			return L"WS_POPUP";

		case DlgFlags::flag::FLAG_WS_THICKFRAME:
			return L"WS_THICKFRAME";

		case DlgFlags::flag::FLAG_DS_MODALFRAME:
			return L"DS_MODALFRAME";
	}
}