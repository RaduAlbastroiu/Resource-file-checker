#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "width_issue.h"


//Widget width issue
vector <wstring> width_issue::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L"    type: " };
	wstring ID = { L" ID: " };

	//issue message
	output_text.push_back(L"  This controller has a non standard width: \n");

	//Controller
	output_text.push_back(type);
	output_text.push_back(dimension_issue_obj.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(dimension_issue_obj.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(dimension_issue_obj.row));
	output_text.push_back(L"\n");

	return output_text;
}
//constructor for the method above ^
width_issue::width_issue(widget obj)
{
	dimension_issue_obj.ID = obj.Get_ID();
	dimension_issue_obj.type = obj.Get_type();
	dimension_issue_obj.row = obj.Get_row();
}