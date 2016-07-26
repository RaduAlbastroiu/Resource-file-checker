#pragma once
//===========================
//Control block class header:
//===========================


#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"



class Control_block
{
	private:
		vector<wstring> requested_dialogs;
		vector<wstring> requested_validators;
		bool tested_dialogs_customization;
		bool validation_customization;

		void Do_The_job(string intput_file);

		//returns true if a dialog should be tested 
		bool Should_be_tested(const wstring &ID);
		
	public:	
		Control_block(const vector<wstring> &dialogs, const vector<wstring> &validators);

		void Check_All_Dialogs(string Line) { this->Do_The_job(Line); return; }
};