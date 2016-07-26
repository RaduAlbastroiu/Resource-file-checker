#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"

//GROUPBOX padding issues
class padding_groupbox_issue : public Issue
{
public:
	virtual vector<wstring> Create_message() = 0;
	padding_groupbox_issue(wstring ID1, wstring ID2, wstring type1, wstring type2, int row1, int row2);

protected:
	struct padding
	{
		wstring ID;
		wstring type;
		int row;
	};
	padding first, second;
};