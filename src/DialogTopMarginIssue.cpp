#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "DialogTopMarginIssue.h"

DialogTopMarginIssue::DialogTopMarginIssue(const int &currentMargin, const int &expectedMargin) {
	current = int_to_wstring(currentMargin);
	expected = int_to_wstring(expectedMargin);
}

vector<wstring> DialogTopMarginIssue::Create_message() {

	vector<wstring> outputText;
	outputText.push_back(L"  Dialog top margin:    Found:" + current + L"     Expected: " + expected + 
						 L" or greater\n\n\n");

	return outputText;
}