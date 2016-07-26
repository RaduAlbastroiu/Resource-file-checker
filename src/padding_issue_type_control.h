
#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_issue.h"


class padding_issue_type_control : public padding_issue
{
	public:
		//constructor
		padding_issue_type_control(widget widget_a, widget widget_b);

	private:
		virtual vector<wstring> Create_message() override;
};
