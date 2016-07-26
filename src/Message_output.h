#pragma once
//=====================
//Message class header:
//=====================

#include "stdafx.h"
#include "Dialog_box.h"
#include "Valid.h"

class Message_output
{
	public:

		void Message_out(vector<wchar_t> s);
		void Message_out(wstring str);
		void Message_out(vector<wstring> str);
		void New_line();
		void New_space();
		void Dialog_ID(wstring ID);
		void File_openfail();
		void No_errors();
		void Nr_issues_type(Valid &v);
		void Final();	
};