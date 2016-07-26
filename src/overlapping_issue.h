#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"

class overlapping_issue :public Issue
{
private:
	virtual vector <wstring> Create_message() override;

public:
	struct overlapping
	{
		wstring ID;
		wstring type;
		int row;
	}first, second;

	//constructor
	overlapping_issue(vector < widget > vect);
};