#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "padding.h"
#include "padding_for_min_distance.h"
#include "padding_first_layer.h"
#include "padding_issue_vertically.h"
#include "padding_issue_horizontally.h"
#include "padding_issue_top.h"
#include "padding_issue_bot.h"
#include "padding_issue_right.h"
#include "padding_issue_left.h"
#include "padding_issue_type_control.h"


// Mark all the widgets as unchecked
padding::padding(const vector<widget> &Dialog_controllers) {

	dialogElements = Dialog_controllers;
}

// Main padding method (it calls the other methods)
void padding::check_padding(Dialog_box &dialog, Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers)
{

	// Check padding from the first to the last controller
	// The issue is reported only if the distance is smaller than minimum
	padding_for_min_distance obj(dialogElements);
	obj.check_padding_for_min_distance(Accumulate_Issues);

	/*
	padding_first_layer first_layer(dialogElements);
	first_layer.check_padding_first_layer(Accumulate_Issues);
	*/
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


// check the top distance between the uppermost controller of a groupbox and the groupbox itself
// distance = abs (groupbox.top - controller.top)
void padding::valid_check_top_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	//find the uppermost controller
	auto child = **min_element(children.begin(), children.end(),
		[](widget const*a, widget const *b) {
		return a->Get_top() < b->Get_top();
	});

	//test the child and the groupbox, push issue if the required distance is not respected
	if (child.Get_top() - father.Get_top() != group_box_top_child)
	{

		// increase nr of this type of issue
		nrissues_padding_groupbox_top++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_top>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

//check the bottom distance between the lowermost controller of a groupbox and the groupbox itself
//distance = abs (groupbox.bottom - controller.bottom)
void padding::valid_check_bot_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the lowermost pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	auto child = **max_element(children.begin(), children.end(),
		[](widget const*a, widget const *b) {
		return a->Get_bottom() < b->Get_bottom();
	});

	//test the child and the groupbox, push issue if the required distance is not respected
	if (father.Get_bottom() - child.Get_bottom() != group_box_bot_child)
	{

		// increase nr of this type of issue
		nrissues_padding_groupbox_bot++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_bot>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

//check the left distance between the leftmost controller of a groupbox and the groupbox itself
//distance = abs (groupbox.left - controller.left)
void padding::valid_check_left_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	//find the leftmost controller
	auto child = **min_element(children.begin(), children.end(),
		[](widget const*a, widget const *b) {
		return a->Get_left() < b->Get_left();
	});

	//test the child and the groupbox, push issue if the required distance is not respected
	if (child.Get_left() - father.Get_left() != group_box_left1_child && child.Get_left() - father.Get_left() != group_box_left2_child)
	{

		// increase nr of this type of issue
		nrissues_padding_groupbox_left++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_left>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

//check the right distance between the rightmost controller of a groupbox and the groupbox itself
//distance = abs (groupbox.right - controller.right)
void padding::valid_check_right_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	//find the rightmost controller
	auto child = **max_element(children.begin(), children.end(),
		[](widget const*a, widget const *b) {
		return a->Get_right() < b->Get_right();
	});

	//test the child and the groupbox, push issue if the minimum required distance is not respected
	if (father.Get_right() - child.Get_right() < minimum_dist_group_box_right_child)
	{

		// increase nr of this type of issue
		nrissues_padding_groupbox_right++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_right>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}