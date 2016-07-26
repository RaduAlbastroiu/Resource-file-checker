#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_groupbox_issue.h"

class padding_issue_bot : public padding_groupbox_issue
{
public:

	//constructor
	padding_issue_bot(widget widget_a, widget widget_b);

private:
	virtual vector<wstring> Create_message() override;


};