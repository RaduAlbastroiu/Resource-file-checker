#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "standard_dimensions.h"
#include "height_issue.h"
#include "width_issue.h"
#include "padding.h"
#include "padding_for_min_distance.h"
#include "padding_issue_vertically.h"
#include "padding_issue_horizontally.h"
#include "padding_issue_top.h"
#include "padding_issue_bot.h"
#include "padding_issue_right.h"
#include "padding_issue_left.h"
#include "padding_issue_type_control.h"
#include "padding_groupbox_issue.h"
#include "padding_groupbox_margins.h"



// constructor
padding_groupbox_margins::padding_groupbox_margins(vector<widget>& dialog_elements)
	:Dialog_controllers(dialog_elements)
{
}



void padding_groupbox_margins::check_padding_groupbox_margins(Accumulator &Accumulate_Issues)
{
	
	for (auto it : Dialog_controllers)
	{
		if (it.Is_groupbox())
		{
			valid_check_top_groupbox(it, Accumulate_Issues);
			valid_check_bot_groupbox(it,Accumulate_Issues);
			valid_check_left_groupbox(it, Accumulate_Issues);
			valid_check_right_groupbox(it, Accumulate_Issues);
		}
	}
	
}



// check the top distance between the uppermost controller of a groupbox and the groupbox itself
// distance = abs (groupbox.top - controller.top)
void padding_groupbox_margins::valid_check_top_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	widget child;

	int MIN = Dialog_max_dimension;

	for (auto it : children)
	{
		if (it->Get_top() < MIN && it->Get_top() >= father.Get_top())
		{
			MIN = it->Get_top();
			child = *it;
		}
	}

	if (MIN != Dialog_max_dimension && 
		((MIN - father.Get_top() < Dialog_top_min_margin) || (MIN - father.Get_top() > Dialog_top_max_margin)))
	{
		// increase nr of this type of issue
		nrissues_padding_groupbox_top++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_top>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

//check the bottom distance between the lowermost controller of a groupbox and the groupbox itself
//distance = abs (groupbox.bottom - controller.bottom)
void padding_groupbox_margins::valid_check_bot_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	widget child;

	int MAX = Dialog_min_dimension;

	for (auto it : children)
	{
		if (it->Get_bottom() > MAX && it->Get_bottom() <= father.Get_bottom())
		{
			MAX = it->Get_bottom();
			child = *it;
		}
	}

	if (MAX != Dialog_min_dimension &&
		((father.Get_bottom() - MAX < Dialog_bot_min_margin) || (father.Get_bottom() - MAX > Dialog_bot_max_margin)))
	{
		// increase nr of this type of issue
		nrissues_padding_groupbox_bot++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_bot>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

//check the left distance between the leftmost controller of a groupbox and the groupbox itself
//distance = abs (groupbox.left - controller.left)
void padding_groupbox_margins::valid_check_left_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	widget child;

	int MIN = Dialog_max_dimension;

	for (auto it : children)
	{
		if (it->Get_left() < MIN && it->Get_left() >= father.Get_left())
		{
			MIN = it->Get_left();
			child = *it;
		}
	}

	if (MIN != Dialog_max_dimension &&
		(( MIN - father.Get_left() < Dialog_left_min_margin) || (MIN - father.Get_left() > Dialog_left_max_margin)))
	{
		// increase nr of this type of issue
		nrissues_padding_groupbox_left++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_left>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

//check the right distance between the rightmost controller of a groupbox and the groupbox itself
//distance = abs (groupbox.right - controller.right)
void padding_groupbox_margins::valid_check_right_groupbox(const widget& father, Accumulator &Accumulate_Issues)
{
	//copy the children pointers vector
	vector<widget*> children = father.get_pointers_to_children();

	widget child;

	int MAX = Dialog_min_dimension;

	for (auto it : children)
	{
		if (it->Get_right() > MAX && it->Get_right() <= father.Get_right())
		{
			MAX = it->Get_right();
			child = *it;
		}
	}

	if (MAX != Dialog_min_dimension &&
		((father.Get_right() - MAX < Dialog_rigt_min_margin) || (father.Get_right() - MAX > Dialog_right_max_margin)))
	{
		// increase nr of this type of issue
		nrissues_padding_groupbox_right++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_right>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}