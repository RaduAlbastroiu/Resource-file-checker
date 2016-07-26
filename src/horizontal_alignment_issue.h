#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"


class horizontal_alignment_issue :public Issue
{
	private:
		virtual vector <wstring> Create_message() override;

	public:
		struct rows
		{
			wstring ID;
			wstring type;
			int row;
		}first, second;

		//constructor
		horizontal_alignment_issue(vector < widget > vect);
};