#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "DialogLeftMarginIssue.h"

DialogLeftMarginIssue::DialogLeftMarginIssue(const int &currentMargin, const int &expectedMargin) {
	current = int_to_wstring(currentMargin);
	expected = int_to_wstring(expectedMargin);
}

vector<wstring> DialogLeftMarginIssue::Create_message() {

	vector<wstring> outputText;
	outputText.push_back(L"  Dialog left margin:    Found:" + current + L"     Expected: " + expected + L"\n\n\n");

	return outputText;
}