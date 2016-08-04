#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"

#define standard_dimension_for_CHECKBOX 10
#define standard_dimension_for_DEFPUSHBUTTON 14
#define standard_dimension_for_EDITTEXT 14
#define standard_dimension_for_bigger_EDITEXT 20
#define standard_dimension_for_PUSHBUTTON 14
#define standard_dimension_for_text 8

#define special_case_check_box_min 10
#define special_case_check_box_max 16
#define special_case_check_box_verification_distance 10

class standard_dimensions : public Valid
{
	public:
		void check_dimensions(Accumulator &Accumulate_Issues, const vector<widget> &Dialog_controllers);

	private:
		struct standard
		{
			int height;
			int width;
		};
		unordered_map<wstring, standard> standard_dimension_map;

		vector<widget> Dialog_controllers;

		// initialize dimension only for standard dimensions
		void initializeDimension();

		void initialize_vect_of_widgets(const vector<widget> &Dialog_controllers);

		int check_dimensions_special_case(const widget &controller);
			int Check_radio_buttons_dimensions(const widget &controller);
			int Check_text_dimensions(const widget &controller);
			int Check_for_bigger_editext(const widget &controller);

		//returns true if height is valid
		int is_Valid_Height(const widget &w, int height);
		
		// returns true if the controller is part of the white list
		bool white_list(const widget &controller);
			bool Check_for_custom_check_box_before_groupbox(const widget &controller);

};
