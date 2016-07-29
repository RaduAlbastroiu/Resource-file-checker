#pragma once
//=============
//Dialog items:
//=============

#include "stdafx.h"
#include "widget.h"
#include "Parsare_Input.h"
#include "widget.h"

class Dialog_box
{
	private:
		vector<widget> Dialog_elements;
		wstring ID = L"";
		int widht = 0;
		int height = 0;
		int row = 0;
		bool tested = false;

		// flags
		bool flagWS_THICKFRAME = false;
		bool flagWS_CHILD	   = false;
		bool flagWS_SYSMENU    = false;
		bool flagWS_CAPTION    = false;
		bool flagWS_POPUP      = false;
		bool flagDS_MODALFRAME = false;
		bool flagWS_BORDER	   = false;
		bool flagWS_SCROLL	   = false;

		// possible buttons of a modal dialog
		bool buttonOK	  = false;
		bool buttonCancel = false;


	public:

		//copy constructor for dialog
		Dialog_box(const Dialog_box &dialog);

		//constructor
		Dialog_box(Parsare &OBJ);

		void Change_ID(wstring name) { this->ID = name; }
		wstring Get_ID() { return this->ID; }

		void Change_width(int x) { this->widht = x; }
		int Get_width() { return this->widht; }

		//changes the height of the dialog
		void Change_height(int x) { this->height = x; }
		int Get_height() { return this->height; }

		//returns the size of the Dialog_elements container
		int Get_nr_elements() { return static_cast<int>( Dialog_elements.size() ); }

		//returns the i-th element
		widget Get_element(int i) { return Dialog_elements[i]; }

		void Change_row(int x) { this->row = x; }
		int Get_row()const { return this->row; }

		//returns true if this dialog should be tested
		bool Should_be_tested() { return tested; }

		// functions for quering dialog flags
		bool hasFlagWS_THICKFRAME()	 const { return flagWS_THICKFRAME; }
		bool hasFlaWS_CHILD()		 const { return flagWS_CHILD; }
		bool hasFlagWS_SYSMENU()	 const { return flagWS_SYSMENU; }
		bool hasFlagWS_CAPTION()	 const { return flagWS_CAPTION; }
		bool hasFlagWS_POPUP()		 const { return flagWS_POPUP; }
		bool hasFlagDS_MODALFRAME()  const { return flagDS_MODALFRAME; }
		bool hasFlagWS_BORDER()		 const { return flagWS_BORDER; }
		bool hasFlagWS_SCROLL()		 const { return flagWS_SCROLL; }

		// functions for setting OK and Cancel buttons for modal frames
		void setButtonOK()		{ buttonOK = true; }
		void setButtonCancel()  { buttonCancel = true; }

		// functions for quering buttons
		bool hasButtonOK()		const { return buttonOK; }
		bool hasButtonCancel()  const { return buttonCancel; }

		// the function that sets all the flags of a read line
		void setFlags(const wstring &Line);

		// function for setting the flags of the OK and Cancel buttons
		void setButtons(const vector<widget> &dialogElements);

		// returns true if the dialog is a frame
		bool isFrame();
		// returns true if the dialog is modal
		bool isModal();

		//returns true if the dialog contains widget elem
		bool containsWidget(const widget &elem) const ;

};