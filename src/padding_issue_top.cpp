#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_groupbox_issue.h"
#include "padding_issue_top.h"


// GROUPBOX Issue top constructor
padding_issue_top::padding_issue_top(widget widget_a, widget widget_b) :
	padding_groupbox_issue(widget_a.Get_ID(), widget_b.Get_ID(), widget_a.Get_type(), widget_b.Get_type(), widget_a.Get_row(), widget_b.Get_row())
{}
// create message method
vector<wstring> padding_issue_top::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L" type: " };
	wstring ID = { L" ID: " };

	//issue ID
	output_text.push_back(L"  The following controller does not respect the top padding for its groupbox\n");

	//controller 1
	output_text.push_back(L"    Groupbox: ");
	output_text.push_back(type);
	output_text.push_back(this->first.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(this->first.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(this->first.row));
	output_text.push_back(L"\n");

	//controller 2
	output_text.push_back(L"    Controller: ");
	output_text.push_back(type);
	output_text.push_back(this->second.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(this->second.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(this->second.row));
	output_text.push_back(L"\n");

	output_text.push_back(L"\n\n");

	//return the output_text
	return output_text;
}