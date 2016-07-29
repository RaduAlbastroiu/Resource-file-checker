#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "DialogTopMarginIssue.h"
#include "DialogMargins.h"

DialogTopMarginIssue::DialogTopMarginIssue(const int &currentMargin, const int &expectedMargin) {

	// for a frame dialog (not modal) the margin can be greater
	greater = (expectedMargin != MODAL_TOP_MARGIN ? L" or greater" : L"");

	current = int_to_wstring(currentMargin);
	expected = int_to_wstring(expectedMargin);
}

vector<wstring> DialogTopMarginIssue::Create_message() {

	vector<wstring> outputText;

	outputText.push_back(L"  Dialog top margin:    Found:" + current + L"     Expected: " + expected + 
						 greater + L"\n\n\n");

	return outputText;
}