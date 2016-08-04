//=================
//Head for reading:
//=================

#pragma once
#include "stdafx.h"
#include "widget.h"

#define Codepage_ENG 1252 //Standard English for windows

class Dialog_box;

class Parsare
{
	private:
		
		//==========
		//variabile:
		int i, n;
		int x, y, width, height;
		int current_row;

		std::wifstream fin;
		int codepage;
		bool utf16 = false;
		bool customized_output = false;
		//all the controllers
		vector< pair <wstring, int> > Controllers;

		vector<wstring> requested_dialogs;

		// =====
		//methods:

		//Find and set the encoding of the input stream
		void Get_encoding(const string &aFilename, wifstream &fin, bool &code_page);

		//Find and return the codepage
		wstring Get_Codepage(const string & aFilename);

		//convert widestring to string
		string ws2s(const wstring& s);

		//Read a single line at a time
		wstring Read_Line(wistream &in);

		/*takes all the controllers of an dialog
		 from the input and keeps them in a vector 
		 of wstrings*/
		bool Take_controller(Dialog_box &dialog);

		

		vector<widget> Dialog_read(Dialog_box &dialog);
		
			void Skip_text(bool &valid, Dialog_box &dialog);
			
			widget Parsare_line(wstring &Line);
				
				void Parsare_tip(wstring &Line, widget &OBJ);
				void Parsare_tab(wstring &Line, widget &OBJ);
				void drop_list_check(const wstring &line, widget &control);
				void Parsare_group(wstring &Line, widget &OBJ);
				void Parsare_radio_button(wstring &Line, widget &OBJ);
				void Parsare_transparent(wstring &Line, widget &OBJ);
				void Parsare_check_box(wstring &Line, widget &OBJ);
				void Parsare_spin_button(wstring &line, widget &OBJ);
				void Parsare_name(wstring &Line, widget &OBJ);
				void Parsare_ID(wstring &Line, widget &OBJ);
				void Parsare_Set_position(wstring &Line, widget &OBJ);
					int char_to_int(wstring &Line);

	public:
		//constructor
		Parsare(const string &File_name, const vector<wstring> &requested_dialog_ids);

		bool Is_open() const;
		bool good() const;
		void Skip_first();

		//reads the dialog IDS given by the user
		void Read_requested_dialogs();

		//returns true if the user doesn't ask for specific dialogs or
		//in case the user did ask for a customized output, returns true if
		//the dialog with this specific ID was asked for
		bool Is_requested_dialog(const wstring &ID);

		//returns true if there are still dialogs asked by the user not yet 
		//validated
		//returns true if user does not ask for customized dialog output
		bool keep_reading();

		int Get_nr_line()const { return this->current_row; }

		wstring find_dialog_IDnr(int &width, int &height, int &row);
		
		vector<widget> Get_dialog(Dialog_box &dialog) { return Dialog_read(dialog); }
};