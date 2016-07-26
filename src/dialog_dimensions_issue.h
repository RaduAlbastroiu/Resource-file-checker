#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"


class dialog_dimensions_issue : public Issue
{
private:
	virtual vector <wstring> Create_message() override;

public:
	struct dialog_dimensions
	{
		wstring ID;
		wstring height;
		wstring width;
	}first;

	//constructor
	dialog_dimensions_issue(Dialog_box &dialog);
};