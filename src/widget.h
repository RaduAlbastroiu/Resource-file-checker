#pragma once

//=================================
//rect elements in the header file:

#include "stdafx.h"

#define drop_list_height 12		//standard drop_list height

class widget
{
	public:
		//Operator overloading
		bool operator==(const widget A);
		bool operator!=(const widget A);

		//constructor
		widget();

		// set the position of the current object
		void Set_position(int x, int y, int height, int width);

		// functions for changing and returning the row of the current object
		void Change_row(int x) { this->Line = x; }
		int Get_row() const { return this->Line; }

		//functions for returning the coordinates of the widget
		int Get_top()const { return Position.top; }
		int Get_bottom()const { return Position.bottom; }
		int Get_left()const { return Position.left; }
		int Get_right()const { return Position.right; }

		//father & child functions commented in the source file
		void Change_father(widget* obj);
		bool Has_father();
		widget Get_father() const;
		widget* Get_father_pointer() const;
		size_t Get_nr_children();
		vector<widget*> get_pointers_to_children() const;
		void change_pointers_to_children(const vector<widget*> &new_Children);
		
		//functions for droplist check
		void Set_drop_list();
		bool Is_drop_list() const;

		//functions for check_button
		void Set_checkbox(bool x) { this->checkbox = x; }
		bool Is_checkbox() const;

		//functions for setting and returning the depth of a widget
		void Set_deep(int x) { this->deep = x; }
		int Get_deep() const { return this->deep; }

		//sets validation
		void Set_valid(int x) { valid = x; }
		//returns validation
		int Get_valid() { return valid; }

		//sets the type of the widget
		void Set_type(const wstring &new_type) { this->type = new_type; }
		//returns the type of the widget
		wstring Get_type()const { return type; }


		//sets the ID of the widget
		void Set_ID(const wstring &new_ID) { this->ID = new_ID; }
		//returns the ID of the widget
		wstring Get_ID() const { return ID; }

		//sets the name of a widget
		void Set_name(const wstring &new_name) { name = new_name; }
		//returns the name of a widget
		wstring Get_name() const { return name; }
		//returns true if the widget has a name
		bool Has_name() const { return name != L""; }

		// setting tab validation
		void Change_Tab_valid(bool x) { this->Tab_validation = x; }

		// returning tab validation
		bool Get_Tab_valid()const { return Tab_validation; }

		// setting group validation
		void Change_group(bool x) { this->Ws_group = x; }

		// return the group validation
		bool Get_Ws_group()const { return Ws_group; }

		// Change radiobutton t/f
		void Set_radio_button(bool x) { this->Radio_button = x; }

		// Get Radio button t/f
		bool Is_radio_button() const { return this->Radio_button; }

		//Change radio button group
		void Change_radio_button_group(int x) { this->Radio_button_group = x; }

		//Get radio button group
		auto Get_radio_button_group() { return this->Radio_button_group; }

		//Widget transparency
		void Set_transparent(bool x) { this->transparent = x; }

		bool Is_groupbox() const { return type == L"GROUPBOX"; }

		//Is widget transparent
		bool Is_transparent() const { return type == L"GROUPBOX" && name == L""; }

		//returns true if the controller is a browse button
		bool Is_browse_button() const;

		//return true if containts the mid of obj
		bool contains_mid_of(const widget &obj) const;

		//returns true if the controller's type ia pushbutton
		bool isPushButton() const { return type == L"PUSHBUTTON"; }

		//returns true if the controller's type is defpushbutton
		bool isDefPushButton() const { return type == L"DEFPUSHBUTTON"; }

		//returns true if the controller's type is text label
		bool isTextLabel() const { return type == L"LTEXT" || type == L"CTEXT" || type == L"RTEXT"; }

		//returns true if the controller's type is edittext
		bool isEditText() const { return type == L"EDITTEXT"; }

		//retuns true if the controller's type is listbox
		bool isListBox() const { return type == L"LISBOX"; }

		// returns true if the controller is type control
		bool isControl() const { return type == L"CONTROL"; }

		//set a widget as spin button
		void setSpinButton() { spinButton = true; }
		//checks if a widget is a spin button
		bool isSpinButton() const { return spinButton; }



	private:
		struct margins
		{
			int top;
			int bottom;
			int left;
			int right;
		};
		
		widget* father = NULL;
		vector<widget*> child;

		margins Position;

		bool Tab_validation = false;
		bool Ws_group		= false;
		bool Radio_button	= false;
		bool drop_list		= false;
		bool checkbox		= false;
		bool transparent	= false;
		bool spinButton		= false;

		int Radio_button_group = 0;
		int width;
		int height;
		int valid = 0;
		wstring type;
		wstring ID;
		wstring name = L"";
		int Line;
		int deep;
};
