#include "stdafx.h"
#include "widget.h"
#include "Issue.h"
#include "DlgFlags.h"
#include "DlgFlagsIssue.h"

DlgFlagsIssue::DlgFlagsIssue(vector < pair<DlgFlags::action, DlgFlags::flag> > suggestionsForFix):
	suggestions(suggestionsForFix)
{
}

vector<wstring> DlgFlagsIssue::Create_message() {

	vector<wstring> outputText;

	// output indentation
	wstring indentation = L"   ";

	for (const auto &suggestion : suggestions) {

		// convert the action and the flag from enum to wstring
		wstring flag   = flagToWstring(suggestion.second);
		wstring action = actionToWstring(suggestion.first);

		// put them in the returned output text
		outputText.push_back(indentation + action + L" flag " + flag + L"\n");
	}
	outputText.push_back(L"\n");

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