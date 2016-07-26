#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "column_alignment_issue.h"


//Column alignment issue
vector <wstring> column_alignment_issue::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L" type: " };
	wstring ID = { L" ID: " };

	//issue message
	output_text.push_back(L"  This controller is not properly vertically aligned:\n");
	output_text.push_back(L"  Controller should probably be aligned to column: ");
	output_text.push_back(int_to_wstring(element.col));
	output_text.push_back(L"\n   ");

	//Controller
	output_text.push_back(type);
	output_text.push_back(element.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(element.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(element.row));
	output_text.push_back(L"\n\n");
	return output_text;
}
//constructor for the method above ^
column_alignment_issue::column_alignment_issue(widget obj, int col)
{
	element.ID = obj.Get_ID();
	element.type = obj.Get_type();
	element.row = obj.Get_row();
	element.col = col;
}