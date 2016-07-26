#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"

class DialogTopMarginIssue : public Issue {
public:
	DialogTopMarginIssue(const int &currentMargin, const int &expectedMargin);

private:
	wstring current;
	wstring expected;

	virtual vector <wstring> Create_message() override;
};
