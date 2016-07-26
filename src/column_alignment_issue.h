#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"


class column_alignment_issue :public Issue
{
private:
	virtual vector <wstring> Create_message() override;
	struct column
	{
		wstring ID;
		wstring type;
		int row;
		int col;
	};
	column element;

public:
	//constructor
	column_alignment_issue(widget obj, int col);
};
