#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_issue.h"
#include "padding_issue_type_control.h"


padding_issue_type_control::padding_issue_type_control(widget widget_a, widget widget_b) :
	padding_issue(widget_a.Get_ID(), widget_b.Get_ID(), widget_a.Get_type(), widget_b.Get_type(), widget_a.Get_row(), widget_b.Get_row())
{}
vector<wstring> padding_issue_type_control::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L" type: " };
	wstring ID = { L" ID: " };

	//issue ID
	output_text.push_back(L"  In the following GROUP of controllers there is a padding issue:\n");

	//controller 1
	output_text.push_back(L"    Top of the GROUP is: ");
	output_text.push_back(type);
	output_text.push_back(first.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(first.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(this->first.row));
	output_text.push_back(L"\n");

	output_text.push_back(L"\n\n");

	//return the output_text
	return output_text;
}
