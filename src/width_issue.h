#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"

class width_issue :public Issue
{
private:
	virtual vector <wstring> Create_message() override;
	struct dimension_items
	{
		wstring ID;
		wstring type;
		int row;
	};
	dimension_items dimension_issue_obj;

public:

	//constructor
	width_issue(widget obj);
};
