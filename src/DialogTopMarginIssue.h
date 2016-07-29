#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"

class DialogTopMarginIssue : public Issue {
public:
	DialogTopMarginIssue(const int &currentMargin, const int &expectedMargin);

private:

	// current and expected margins converted to wstring
	wstring current;
	wstring expected;

	// for a frame dialog top margin is flexible so it can be equal to the
	// distance defined or greater
	wstring greater;

	virtual vector <wstring> Create_message() override;
};
