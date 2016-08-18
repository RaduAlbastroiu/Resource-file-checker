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
		if (it.Is_groupbox() && !it.Is_transparent())
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

	// If there is a transparent groupbox in the father groupbox
	// all the kids from the transparent groupbox are checked
	complete_vect_of_kids(children);

	widget child;

	int MIN = Dialog_max_dimension;

	if (children.size() < 2)
		return;

	for (auto it : children)
	{
		if (it->Get_top() < MIN && it->Get_top() >= father.Get_top())
		{
			if (!is_on_white_list(*it))
			{
				MIN = it->Get_top();
				child = *it;
			}
		}
	}

	// No issue if the distance is too big
	if (MIN - father.Get_top() > Dialog_maxim_comparison_distance)
		return;

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

	// If there is a transparent groupbox in the father groupbox
	// all the kids from the transparent groupbox are checked
	complete_vect_of_kids(children);
	
	widget child;

	int MAX = Dialog_min_dimension;

	if (children.size() < 2)
		return;

	for (auto it : children)
	{
		if (it->Get_bottom() > MAX && it->Get_bottom() <= father.Get_bottom())
		{
			if (!is_on_white_list(*it))
			{
				MAX = it->Get_bottom();
				child = *it;
			}
		}
	}

	// No issue if the distance is too big
	if (father.Get_bottom() - MAX > Dialog_maxim_comparison_distance)
		return;

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

	// If there is a transparent groupbox in the father groupbox
	// all the kids from the transparent groupbox are checked
	complete_vect_of_kids(children);

	widget child;

	int MIN = Dialog_max_dimension;

	if (children.size() < 2)
		return;

	for (auto it : children)
	{
		if (it->Get_left() < MIN && it->Get_left() >= father.Get_left())
		{
			if (!is_on_white_list(*it))
			{
				MIN = it->Get_left();
				child = *it;
			}
		}
	}

	// No issue if the distance is too big
	if (MIN - father.Get_left() > Dialog_maxim_comparison_distance)
		return;

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

	// If there is a transparent groupbox in the father groupbox
	// all the kids from the transparent groupbox are checked
	complete_vect_of_kids(children);

	widget child;

	int MAX = Dialog_min_dimension;

	if (children.size() < 2)
		return;

	for (auto it : children)
	{
		if (it->Get_right() > MAX && it->Get_right() <= father.Get_right())
		{
			if (!is_on_white_list(*it))
			{
				MAX = it->Get_right();
				child = *it;
			}
		}
	}

	// No issue if the distance is too big
	if (father.Get_right() - MAX > Dialog_maxim_comparison_distance)
		return;

	if (MAX != Dialog_min_dimension &&
		((father.Get_right() - MAX < Dialog_rigt_min_margin) || (father.Get_right() - MAX > Dialog_right_max_margin)))
	{
		// increase nr of this type of issue
		nrissues_padding_groupbox_right++;

		unique_ptr<Issue> pointer = make_unique<padding_issue_right>(father, child);

		Accumulate_Issues.push_issue(move(pointer));
	}
}

bool padding_groupbox_margins::is_on_white_list(const widget & controller)
{
	if (controller.isSpinButton())
		return true;
	
	if (controller.Is_browse_button())
		return true;

	if (controller.isTextLabel() && !controller.Has_name())
		return true;

	if (controller.Is_groupbox() && controller.Is_transparent())
		return true;

	return false;
}

void padding_groupbox_margins::complete_vect_of_kids(vector<widget*> &children)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->Is_groupbox() && children[i]->Is_transparent())
		{
			if (children[i]->get_pointers_to_children().size())
			{
				for (auto it_transparent : children[i]->get_pointers_to_children())
				{
					if (it_transparent->Get_bottom() <= children[i]->Get_bottom() &&
						it_transparent->Get_top() >= children[i]->Get_top() &&
						it_transparent->Get_left() >= children[i]->Get_left() &&
						it_transparent->Get_right() <= children[i]->Get_right())
						children.push_back(it_transparent);
				}
			}
		}
	}
}
