#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"

class height_issue :public Issue
{
	private:
		virtual vector <wstring> Create_message() override;
		struct dimension_items
		{
			wstring ID;
			wstring type;
			int row;
			int place_to_be;
		};
		dimension_items dimension_issue_obj;

	public:

	//constructor
	height_issue(widget obj, int place_to_be);
};
