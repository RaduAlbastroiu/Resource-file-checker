#pragma once

#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_issue.h"


class padding_issue_vertically : public padding_issue
{
public:
	//constructor
	padding_issue_vertically(const widget &widget_a, const widget &widget_b, const int &distance);

private:

	int dist;

	virtual vector<wstring> Create_message() override;

	wstring m_distance;
};