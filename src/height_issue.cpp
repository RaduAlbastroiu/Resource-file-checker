#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "height_issue.h"


//Widget height issue
vector <wstring> height_issue::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L"    type: " };
	wstring ID = { L" ID: " };

	//issue message
	output_text.push_back(L"  This controller has a non standard height: \n");

	//Controller
	output_text.push_back(type);
	output_text.push_back(dimension_issue_obj.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(dimension_issue_obj.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(dimension_issue_obj.row));
	output_text.push_back(L"\n");
	output_text.push_back(L"    Suggestion: The height of the widget should be: " + int_to_wstring(dimension_issue_obj.place_to_be));
	output_text.push_back(L"\n\n\n");

	return output_text;
}
//constructor for the method above ^
height_issue::height_issue(widget obj, int place_to_be)
{
	dimension_issue_obj.ID = obj.Get_ID();
	dimension_issue_obj.type = obj.Get_type();
	dimension_issue_obj.row = obj.Get_row();
	dimension_issue_obj.place_to_be = place_to_be;
}
