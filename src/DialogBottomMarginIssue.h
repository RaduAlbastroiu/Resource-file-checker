#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"

class DialogBottomMarginIssue : public Issue {
public:
	DialogBottomMarginIssue(const int &currentMargin, const int &expectedMargin);

private:
	// current and expected margins converted to wstring
	wstring current;
	wstring expected;

	// for a frame dialog bottom margin is flexible so it can be equal to the
	// distance defined or greater
	wstring greater;

	virtual vector <wstring> Create_message() override;
};
