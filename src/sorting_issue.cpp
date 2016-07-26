#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "sorting_issue.h"


//Z-tab oreder sorting issue
vector <wstring> sorting_issue::Create_message()
{

	//============
	int i = 0;
	auto n = sorted.size();
	vector<wstring> output_text;
	wstring type = { L"    type: " };
	wstring ID = { L" ID: " };

	output_text.push_back(L"  The tab order should be: \n");


	for (i = 0; i < n; i++)
	{
		//Controller
		output_text.push_back(type);
		output_text.push_back(sorted[i].type);
		output_text.push_back(L" ");
		output_text.push_back(ID);
		output_text.push_back(sorted[i].ID);
		output_text.push_back(L", found at line: ");
		output_text.push_back(int_to_wstring(sorted[i].row));
		output_text.push_back(L"\n");

	}
	//return the output_text
	return output_text;
}
//constructor for the method above ^
sorting_issue::sorting_issue(vector <widget> vect)
{
	int i = 0;
	auto n = vect.size();
	for (; i < n; i++)
	{
		sort_items item;
		item.ID = vect[i].Get_ID();
		item.type = vect[i].Get_type();
		item.row = vect[i].Get_row();
		sorted.push_back(item);
	}
}
