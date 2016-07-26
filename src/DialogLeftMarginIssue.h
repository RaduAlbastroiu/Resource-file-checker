#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"

class DialogLeftMarginIssue : public Issue {
	public:
		DialogLeftMarginIssue(const int &currentMargin, const int &expectedMargin);

	private:
		wstring current;
		wstring expected;

		virtual vector <wstring> Create_message() override;
};