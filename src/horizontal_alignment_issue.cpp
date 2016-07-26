#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "horizontal_alignment_issue.h"


//Rows alignment issue
vector <wstring> horizontal_alignment_issue::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L" type: " };
	wstring ID = { L" ID: " };

	//issue ID
	output_text.push_back(L"  The following two controllers have a horizontal alignment issue:\n");

	//controller 1
	output_text.push_back(L"    First controller: ");
	output_text.push_back(type);
	output_text.push_back(this->first.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(this->first.ID);
	output_text.push_back(L", found at line: ");
	output_text.push_back(int_to_wstring(this->first.row));
	output_text.push_back(L"\n");

	//controller 2
	output_text.push_back(L"    Second controller: ");
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
//constructor for the method above ^
horizontal_alignment_issue::horizontal_alignment_issue(vector < widget > vect)
{
	first.ID = vect[0].Get_ID();
	second.ID = vect[1].Get_ID();

	first.type = vect[0].Get_type();
	second.type = vect[1].Get_type();

	first.row = vect[0].Get_row();
	second.row = vect[1].Get_row();
}