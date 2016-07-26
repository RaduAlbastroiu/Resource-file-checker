#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"


class sorting_issue :public Issue
{
private:
	virtual vector <wstring> Create_message() override;
	struct sort_items
	{
		wstring ID;
		wstring type;
		int row;
	};
	vector<sort_items> sorted;

public:

	//constructor
	sorting_issue(vector <widget> vect);
};
