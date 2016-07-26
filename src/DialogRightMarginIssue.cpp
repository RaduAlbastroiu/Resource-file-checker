#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "DialogRightMarginIssue.h"

DialogRightMarginIssue::DialogRightMarginIssue(const int &currentMargin, const int &expectedMargin) {
	current = int_to_wstring(currentMargin);
	expected = int_to_wstring(expectedMargin);
}

vector<wstring> DialogRightMarginIssue::Create_message() {

	vector<wstring> outputText;
	outputText.push_back(L"  Dialog right margin:    Found:" + current + L"     Expected: " + expected + L"\n\n\n");

	return outputText;
}