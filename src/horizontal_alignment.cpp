#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "horizontal_alignment.h"
#include "horizontal_alignment_issue.h"


//well defined rows checker
void horizontal_alignment::check_rows(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers)
{
	int i = 0, j = 0;
	auto n = Dialog_controllers.size();

	vector<widget> issue;

	// check all widgets
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			// no issue if one widget is pushbutton named "..."
			if(!((Dialog_controllers[i].Get_type() == L"PUSHBUTTON") &&
				(Dialog_controllers[i].Get_name() == L"..." ||
				(Dialog_controllers[i].Get_bottom() - Dialog_controllers[i].Get_top() <= 10 || Dialog_controllers[i].Get_right() - Dialog_controllers[i].Get_left() <= 10)) ||

				(Dialog_controllers[j].Get_type() == L"PUSHBUTTON" &&
				(Dialog_controllers[j].Get_name() == L"..." ||
				(Dialog_controllers[j].Get_bottom() - Dialog_controllers[j].Get_top() <= 10 || Dialog_controllers[j].Get_right() - Dialog_controllers[j].Get_left() <= 10)))))
			{
				
				if (Dialog_controllers[i].Get_deep() == Dialog_controllers[j].Get_deep())
				// verif if widgets are on the same level
				{
					// verif if widgets are close 
					if (if_close(&Dialog_controllers[i], &Dialog_controllers[j]) &&
						if_same_size(&Dialog_controllers[i], &Dialog_controllers[j]) &&
						!if_cross_line(&Dialog_controllers[i], &Dialog_controllers[j], Dialog_controllers))
					{
						// check for wrong alignment
						bool valid = if_not_aligned(&Dialog_controllers[i], &Dialog_controllers[j]);

						if (valid == true)
						{

							// increase the nr of issues for this type
							nrissues_rows++;

							issue.push_back(Dialog_controllers[i]);
							issue.push_back(Dialog_controllers[j]);

							// create issue obj
							unique_ptr < Issue > pointer = make_unique < horizontal_alignment_issue >(issue);

							// push issue 
							Accumulate_Issues.push_issue(move(pointer));

							issue.clear();

						}
					}
				}
			}
		}
	}
}


// disabled because no issues cathed with this error case
// return true if there is a widget between widget 1 and 2
bool horizontal_alignment::if_cross_line(widget* OBJ1, widget* OBJ2, vector<widget> &Dialog_controllers)
{
	/**/
	auto n = Dialog_controllers.size();

	// extract usefull data from widget 1
	int left3 = OBJ1->Get_left();
	int right3 = OBJ1->Get_right();
	int top3 = OBJ1->Get_top();
	int bot3 = OBJ1->Get_bottom();

	// extract usefull data from widget 2
	int left2 = OBJ2->Get_left();
	int right2 = OBJ2->Get_right();
	int top2 = OBJ2->Get_top();
	int bot2 = OBJ2->Get_bottom();

	// creating the rectangle common to the two widgets
	int top1 = (top3 > top2 )? top3 : top2;
	int bot1 = (bot3 < bot2) ? bot3 : bot2;
	int right1 = (left3 > left2) ? left3 : left2;
	int left1 = (right3 < right2) ? right3 : right2;

	for (int i = 0; i < n; i++)
	{
		// extracting only usefull data from widget 2
		int left2 = Dialog_controllers[i].Get_left();
		int right2 = Dialog_controllers[i].Get_right();
		int top2 = Dialog_controllers[i].Get_top();
		int bot2 = Dialog_controllers[i].Get_bottom();

		// vertical overlapping:
		if (top1 < top2)
		{
			if (top2 < bot1 && bot1 <= bot2)
				if ((left1 < right2 && right2 <= right1) || (left2 < right1 && right1 <= right2))
					return true;
		}
		else
		{
			if (top1 < bot2 && bot2 <= bot1)
				if ((left1 < right2 && right2 <= right1) || (left2 < right1 && right1 <= right2))
					return true;
		}

		// horizontal overlapping
		if (left1 < left2)
		{
			if (left2 < right1 && right1 <= right2)
				if ((top1 < bot2 && bot2 <= bot1) || (top2 < bot1 && bot1 <= bot2))
					return true;
		}
		else
		{
			if (left1 < right2 && right2 <= right1)
				if ((top1 < bot2 && bot2 <= bot1) || (top2 < bot1 && bot1 <= bot2))
					return true;
		}
	}
	return false;
}

// check if the widgets are not properly aligned
bool horizontal_alignment::if_not_aligned(widget* OBJ1, widget* OBJ2)
{
	// extract only usefull data from widget 1 and 2
	int mid1 = (OBJ1->Get_bottom() - OBJ1->Get_top()) / 2 + OBJ1->Get_top();
	int mid2 = (OBJ2->Get_bottom() - OBJ2->Get_top()) / 2 + OBJ2->Get_top();

	// if wrong ->  return true;
	// if good alignment -> return false;
	if (mid1 != mid2)
		return true;
	
	return false;
}

// check if the widgets are close and on the same row
bool horizontal_alignment::if_close(widget* OBJ1, widget* OBJ2)
{
	// extract usefull data from widget 1
	int left1 = OBJ1->Get_left();
	int right1 = OBJ1->Get_right();
	int mid1 = (OBJ1->Get_bottom() - OBJ1->Get_top()) / 2 + OBJ1->Get_top();
	int top1 = OBJ1->Get_top();
	int bot1 = OBJ1->Get_bottom();

	// extract usefull data from widget 2
	int left2 = OBJ2->Get_left();
	int right2 = OBJ2->Get_right();
	int mid2 = (OBJ2->Get_bottom() - OBJ2->Get_top()) / 2 + OBJ2->Get_top();
	int top2 = OBJ2->Get_top();
	int bot2 = OBJ2->Get_bottom();

	// verif if the controllers are on the same row ( not if they are properly alligned )
	if ((top1 <= mid2 && bot1 >= mid2) ||
		(top2 <= mid1 && bot2 >= mid1))
	{
		// verif if the controllers are close 
		if ((right1 <= left2 && left2 - right1 >= 0 && left2 - right1 <= horizontal_distance) ||
			(right2 <= left1 && left1 - right2 >= 0 && left1 - right2 <= horizontal_distance))
		{
			return true;
		}

	}
	return false;
}

// if the widgets are not bigger than max_comparison_height
bool horizontal_alignment::if_same_size(widget* OBJ1, widget* OBJ2)
{
	// extract usefull data from widget 1
	int top1 = OBJ1->Get_top();
	int bot1 = OBJ1->Get_bottom();

	// extract usefull data from widget 2
	int top2 = OBJ2->Get_top();
	int bot2 = OBJ2->Get_bottom();

	// verif if the controllers are smaller than max_comparison_height
	if (bot1 - top1 <= max_comparison_height && bot2 - top2 <= max_comparison_height)
		return true;
	return false;
}