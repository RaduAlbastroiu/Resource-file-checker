#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "padding.h"
#include "padding_for_min_distance.h"
#include "padding_first_layer.h"
#include "padding_groupbox_margins.h"
#include "padding_issue_vertically.h"
#include "padding_issue_horizontally.h"
#include "padding_issue_top.h"
#include "padding_issue_bot.h"
#include "padding_issue_right.h"
#include "padding_issue_left.h"
#include "padding_issue_type_control.h"
#include "padding_groupbox_issue.h"


// Mark all the widgets as unchecked
padding::padding(const vector<widget> &Dialog_controllers) {

	dialogElements = Dialog_controllers;
}

// Main padding method (it calls the other methods)
void padding::check_padding(Dialog_box &dialog, Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers)
{

	// Check padding from the first to the last controller
	// The issue is reported only if the distance is smaller than minimum
	//padding_for_min_distance obj(dialogElements);
	//obj.check_padding_for_min_distance(Accumulate_Issues);

	/* Currently disabled !! 
	   It is functional but there are too many issues

	padding_first_layer first_layer(dialogElements);
	first_layer.check_padding_first_layer(Accumulate_Issues);
	*/

	padding_groupbox_margins obj_groupbox(dialogElements);
	obj_groupbox.check_padding_groupbox_margins(Accumulate_Issues);
}


// Get the key for every type of widget
int padding::getKey(const widget &element) {
	return	element.isPushButton() ? KEY_PUSHBUTTON :
				element.isDefPushButton() ? KEY_DEFPUSHBUTTON :
					element.Is_checkbox() ? KEY_CHECKBOX :
						element.Is_radio_button() ? KEY_RADIOBUTTON :
							element.isTextLabel() ? KEY_TEXTLABEL :
								element.isEditText() ? KEY_EDITTEXT :
									element.Is_groupbox() ? KEY_GROUPBOX :
										element.isListBox() ? KEY_LISTBOX :
											element.Is_drop_list() ? KEY_DROPDOWNLIST :
												element.isControl() ? KEY_CONTROL :
																		KEY_IGNORED_CONTROLLER;
}


bool padding::areListElements(const widget &first, const widget &second) {
	return  (first.isTextLabel() || first.Is_radio_button() || first.Is_checkbox()) &&
		(second.isTextLabel() || second.Is_radio_button() || second.Is_checkbox()) &&
		(!first.isTextLabel() || !second.isTextLabel());
}

bool padding::intersectOnOx(const widget &A, const widget &B) {
	return  !(A.Get_left() >  B.Get_right() || B.Get_left() >  A.Get_right()) &&
		(A.Get_top() >= B.Get_bottom() || B.Get_top() >= A.Get_bottom());
}

bool padding::intersectOnOy(const widget &A, const widget &B) {
	return	 (A.Get_left() >= B.Get_right() || B.Get_left() >= A.Get_right()) &&
		!(A.Get_top() > B.Get_bottom() || B.Get_top() > A.Get_bottom());
}


int padding::getExpVertDistListElems(const widget &first, const widget &second) {
	//first will always be above second

	//check whether second is ending the list of first
	//return the distance specific to the end of the list, or to the start of a new one
	//isToLeft(first, second) returning true means that second starts a new list

	return isToLeft(first, second) ?
		(second.isTextLabel() ? NEW_LIST_TEXTLABEL : NEW_LIST_CHECK_RADIO)
		: END_LIST;
}

//Matrix for determining the vertical distances between two controllers
//Each controller has a key based on its type
//The element of the matrix at the intersection of the two keys represents the distance
//The line is the type key of the element above
//The column is the type key of the element below
//Value -1 means that the specific distance is unknown and therefore ignored
int padding::vertical_distances[10][10] =   {//0   1   2   3   4   5   6   7   8   9
											{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },		//0 KEY_IGNORED_CONTROLLER
											{ -1,  4,  4,  2,  2,  2,  2,  4,  4, -1 },		//1 KEY_PUSHBUTTON
											{ -1,  4,  4,  2,  2,  2,  2,  4,  4, -1 },		//2 KEY_DEFPUSHBUTTON
											{ -1,  2,  2,  2,  2,  4,  2,  2,  2,  2 },		//3 KEY_CHECKBOX
											{ -1,  2,  2,  2,  2,  4,  2,  2,  2,  2 },		//4 KEY_RADIOBUTTON	
											{ -1,  2,  2,  4,  4,  7,  2,  2,  2,  2 },		//5 KEY_TEXTLABEL
											{ -1,  2,  2,  2,  2,  2,  4,  2,  7,  5 },		//6 KEY_EDITTEXT
											{ -1,  4,  4,  2,  2,  2,  2,  7, -1, -1 },		//7 KEY_GROUPBOX
											{ -1,  4,  4,  2,  2,  2,  7, -1, -1,  7 },		//8 KEY_LISTBOX	
											{ -1, -1, -1,  2,  2,  2,  5, -1,  7,  6 },		//9 KEY_DROPDOWNLIST
};
//============================================

//Matrix for determining the horizontal distances between two controllers
//Each controller has a key based on its type
//The element of the matrix at the intersection of the two keys represents the distance
//The line is the type key of the leftmost element
//The column is the type key of the rightmost element
//Value -1 means that the specific distance is unknown and therefore ignored
int padding::horizontal_distances[10][10] = {//0   1   2   3   4   5   6   7   8   9
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },	//0 KEY_IGNORED_CONTROLLER
	{ -1,  4,  4, -1, -1, -1,  4, -1, -1, -1 },	//1 KEY_PUSHBUTTON
	{ -1,  4,  4, -1, -1, -1,  4, -1, -1, -1 },	//2 KEY_DEFPUSHBUTTON
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },	//3 KEY_CHECKBOX
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },	//4 KEY_RADIOBUTTON	
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },	//5 KEY_TEXTLABEL
	{ -1,  4,  4, -1, -1, -1, -1, -1, -1, -1 },	//6 KEY_EDITTEXT
	{ -1, -1, -1, -1, -1, -1, -1,  7, -1, -1 },	//7 KEY_GROUPBOX
	{ -1,  4,  4, -1, -1, -1, -1, -1, -1, -1 },	//8 KEY_LISTBOX	
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },	//9 KEY_DROPDOWNLIST
};
//============================================
