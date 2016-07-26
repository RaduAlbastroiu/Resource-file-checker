#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "dialog_dimensions_issue.h"

//Dialog dimensions issue
vector <wstring> dialog_dimensions_issue::Create_message()
{
	vector<wstring> output_text;
	wstring ID = { L"    ID: " };
	wstring height = { L" height: " };
	wstring width = { L", width: " };

	//issue message
	output_text.push_back(L"  This dialog is too large: \n");

	//Dialog
	output_text.push_back(ID);
	output_text.push_back(first.ID);
	output_text.push_back(L"\n");
	output_text.push_back(height);
	output_text.push_back(first.height);
	output_text.push_back(width);
	output_text.push_back(first.width);
	output_text.push_back(L"\n\n");

	return output_text;
}
//constructor for dialog dimensions
dialog_dimensions_issue::dialog_dimensions_issue(Dialog_box &dialog)
{
	this->first.ID = dialog.Get_ID();

	this->first.height = this->int_to_wstring(dialog.Get_height());

	this->first.width = this->int_to_wstring(dialog.Get_width());
}
