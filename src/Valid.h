#pragma once
//========================
//Validation class header:
//========================

#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Accumulator.h"
#include <unordered_map>

/* 
	These are the standard values,
	But this can be changed easly
*/
#define column_space 4 //distance which is too short in between different columns
#define dialog_height 500 //maximum dialog height
#define dialog_width 500 //maximum dialog width
#define max_unaligned_controlers 2 //maxiumum number of dialogs that can be unalligned
#define standard_vertical_padding 7 //standard vertical padding in between two controllers
#define standard_horizontal_padding 2 //standard vertical padding in between two controllers
#define pushbuttton_horizontal_padding 4 //particular case
#define column_7 7		//number of column 7
#define column_14 14	//number of column 14
#define column_21 21	//number of column 21
#define max_range_of_column_7 10	//between columns 7 and 14, column 10 is the last column in the range of 7
#define max_range_of_column_14 17	//between columns 14 and 21, column 10 is the last column in the range of 14
#define group_box_top_child 12 // comment
#define group_box_bot_child 7 // comment
#define group_box_left1_child 9 // comment
#define group_box_left2_child 10 // comment
#define minimum_dist_group_box_right_child 7 // comment
#define distance_between_controlitems 12
#define distance_min_berween_controlitems 2

class Valid
{
	protected:
		//issues counter
		static int nrissues_dialog_dim;
		static int nrissues_partial_ol;
		static int nrissues_rows;
		static int nrissues_column_alignment;
		static int nrissues_standard_dimensions;
		static int nrissues_padding_vertically;
		static int nrissues_padding_horizontally;
		static int nrissues_padding_groupbox_top;
		static int nrissues_padding_groupbox_bot;
		static int nrissues_padding_groupbox_left;
		static int nrissues_padding_groupbox_right;
		static int nrissues_padding_typecontrol;
		static int nrIssuesDlgFlags;
		static int nrIssuesDialogMargins;
		static int nrissues_sort;


		//data structures
		vector<widget> Dialog_controllers;

		//ADD COMMENTS LATER
		static vector<wstring> requested_validators;
		static bool customized_validation;


		//ONLY for check_box and radio_button
		struct control
		{
			bool check_box = false;
			bool radio_button = false;
			bool good = true;

			int distance = 0;

			vector <widget*> elements;
		};
		vector <control> control_list;
		void create_control_list(vector<widget>::iterator it, vector<widget> &Dialog_controllers);

		//methods

		// Creates the tree 
		// Obj x is child of y if center of x is inside of y
		void create_tree();
			void sort_tree(vector<widget*> &pointeri);


		bool should_be_run(const wstring &validator);

	public:
		void Get_issues(Dialog_box Dialog, Accumulator &Accumulate_Issues);

		int Get_nrissues_dialog_dim() { return nrissues_dialog_dim; }
		int Get_nrissues_partial_ol() { return nrissues_partial_ol; }
		int Get_nrissues_rows() { return nrissues_rows; }
		int Get_nrissues_column_alignment() { return nrissues_column_alignment; }
		int Get_nrissues_standard_dimensions() { return nrissues_standard_dimensions; }
		int Get_nrissues_padding_vertically() { return nrissues_padding_vertically; }
		int Get_nrissues_padding_horizontally() { return nrissues_padding_horizontally; }
		int Get_nrissues_padding_groupbox_top() { return nrissues_padding_groupbox_top; }
		int Get_nrissues_padding_groupbox_bot() { return nrissues_padding_groupbox_bot; }
		int Get_nrissues_padding_groupbox_left() { return nrissues_padding_groupbox_left; }
		int Get_nrissues_padding_groupbox_right() { return nrissues_padding_groupbox_right; }
		int Get_nrissues_padding_typecontrol() { return nrissues_padding_typecontrol; }
		int getNrIssuesDlgFlags()		{ return nrIssuesDlgFlags; }
		int getNrIssuesDialogMargins()	{ return nrIssuesDialogMargins; }
		int Get_nrissues_sort() { return nrissues_sort; }

		static void set_requested_validators(const vector<wstring> &validators);
		static void set_customized_validation(const bool &validation);

};

