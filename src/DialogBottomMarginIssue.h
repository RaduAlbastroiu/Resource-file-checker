#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"

class DialogBottomMarginIssue : public Issue {
public:
	DialogBottomMarginIssue(const int &currentMargin, const int &expectedMargin);

private:
	wstring current;
	wstring expected;

	virtual vector <wstring> Create_message() override;
};
