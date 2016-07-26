#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_issue.h"
#include "padding_issue_vertically.h"

padding_issue_vertically::padding_issue_vertically(const widget &widget_a, const widget &widget_b, const int &distance) :
	padding_issue(widget_a.Get_ID(), widget_b.Get_ID(), widget_a.Get_type(), widget_b.Get_type(), widget_a.Get_row(), widget_b.Get_row())
{
	dist = distance;
}
vector<wstring> padding_issue_vertically::Create_message()
{
	vector<wstring> output_text;
	wstring type = { L" type: " };
	wstring ID = { L" ID: " };

	//issue ID
	output_text.push_back(L"  The following two controllers have a vertical padding issue:\n");

	//controller 1
	output_text.push_back(L"    First controller: ");
	output_text.push_back(type);
	output_text.push_back(first.type);
	output_text.push_back(L" ");
	output_text.push_back(ID);
	output_text.push_back(first.ID);
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

	if (dist < 0)
	{
		dist = (-1)*dist;
		m_distance = int_to_wstring(dist);
		output_text.push_back(L"\tSuggestion: Decrease the vertical distance between them by " + m_distance + L"\n");
	}
	else
	{
		m_distance = int_to_wstring(dist);
		output_text.push_back(L"\tSuggestion: Increase the vertical distance between them by " + m_distance + L"\n");
	}

	output_text.push_back(L"\n\n");

	//return the output_text
	return output_text;
}
