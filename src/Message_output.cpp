//==================
//Message class cpp:
//==================

#include "stdafx.h"
#include "Message_output.h"
#include "Valid.h"

void Message_output::Message_out(vector<wchar_t> s)
{
	int i;
	auto n = s.size();
	for (i = 0; i < n; i++)
	{
		wcout << s[i];
	}
}

void Message_output::Message_out(wstring str)
{
	//Printing the message
	std::wcout << str.c_str();
}

void Message_output::Message_out(vector<wstring> str)
{
	int i;
	auto n = str.size();

	for (i = 0; i < n; i++)
	{
		this->Message_out(str[i]);
	}
}

void Message_output::New_line()
{
	//printing a new line in the console
	cout << "\n";
}

void Message_output::New_space()
{
	//printing a space "_"
	cout << " ";
}

void Message_output::Dialog_ID(wstring ID)
{
	//Dialog number
	cout << " Dialog name: ";
	wcout << ID.c_str();
	cout << "\n\n";
}

void Message_output::File_openfail()
{
	//Open file fail
	cout << " File fail to open !";
}

void Message_output::No_errors()
{
	cout << "\n No errors for this dialog ! \n";
}

void Message_output::Nr_issues_type(Valid &v)
{
	int groupbox = v.Get_nrissues_padding_groupbox_top() + v.Get_nrissues_padding_groupbox_bot() +
		v.Get_nrissues_padding_groupbox_left() + v.Get_nrissues_padding_groupbox_right();
	wcout << L"  Number of issues listed by type:\n";
	wcout << L"    Dialog Flags:           " << v.getNrIssuesDlgFlags() << L'\n';
	wcout << L"    Dialog Margins          " << v.getNrIssuesDialogMargins() << L'\n';
	wcout << L"    Dialog dimensions:      " << v.Get_nrissues_dialog_dim() << L"\n";
	wcout << L"    Widget dimensions:      " << v.Get_nrissues_standard_dimensions() << L"\n";
	wcout << L"    Partial overlapping:    " << v.Get_nrissues_partial_ol() << L"\n";
	wcout << L"    Horizontal alignment:   " << v.Get_nrissues_rows() << L"\n";
	wcout << L"    Column alignment:       " << v.Get_nrissues_column_alignment() << L"\n";
	wcout << L"    Padding vertically:     " << v.Get_nrissues_padding_vertically() << L"\n";
	wcout << L"    Padding horizontally:   " << v.Get_nrissues_padding_horizontally() << L"\n";
	wcout << L"    Padding type control:   " << v.Get_nrissues_padding_typecontrol() << L"\n";
	wcout << L"    Padding GROUPBOX:       " <<   groupbox << L"\n";
	wcout << L"      - groupbox top:       " << v.Get_nrissues_padding_groupbox_top() << L"\n";
	wcout << L"      - groupbox bot:       " << v.Get_nrissues_padding_groupbox_bot() << L"\n";
	wcout << L"      - groupbox left:      " << v.Get_nrissues_padding_groupbox_left() << L"\n";
	wcout << L"      - groupbox right:     " << v.Get_nrissues_padding_groupbox_right() << L"\n";
	wcout << L"    Sorting:                " << v.Get_nrissues_sort() << L"\n";
}

void Message_output::Final()
{
	//End
	cout << "  That's all! ";
}
