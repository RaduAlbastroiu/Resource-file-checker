#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "sorting.h"
#include "sorting_issue.h"


//sorting issue class checker
void sorting::check_sorting(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers)
{
	// copy the elements
	vector<widget> Dialog_controllers_sorted = Dialog_controllers;

	// sort them according to Z-order rules
	sort(Dialog_controllers_sorted.begin(), Dialog_controllers_sorted.end(), comp);

	// check for differences between the order from file and the computed order
	if (!equal(Dialog_controllers.begin(), Dialog_controllers.end(), Dialog_controllers_sorted.begin(), Dialog_controllers_sorted.end()))
	{
		//increase the nr of issues for this type
		nrissues_sort++;

		unique_ptr < Issue > pointer = make_unique < sorting_issue >(Dialog_controllers_sorted);
		Accumulate_Issues.push_issue(move(pointer));
	}
}
void sorting::repair_sort(vector<widget> &controllers)
{
	auto it = controllers.begin();
	auto it2 = controllers.begin();
	bool OK = false;

	for (; it != controllers.end(); it++)
	{
		if (it->Get_radio_button_group())
		{
			while (OK == false)
			{
				OK = true;
				for (it2 = it + 1; it2 != controllers.end(); it2++)
				{
					if ((it2 - 1)->Get_radio_button_group() == 0 &&
						it2->Get_radio_button_group() == it->Get_radio_button_group())
						swap(*(it2 - 1), *it);
				}
			}
		}
	}
}
/*static*/
bool sorting::comp(const widget &OBJ1, const widget &OBJ2)
{
	int top1, top2;
	int bot1, bot2;
	int left1, left2;
	int right1, right2;

	top1 = OBJ1.Get_top();
	bot1 = OBJ1.Get_bottom();
	left1 = OBJ1.Get_left();
	right1 = OBJ1.Get_right();

	top2 = OBJ2.Get_top();
	bot2 = OBJ2.Get_bottom();
	left2 = OBJ2.Get_left();
	right2 = OBJ2.Get_right();

	//Total Overlapping
	if (top2 < top1 && bot2 > bot1 && left2 < left1 && right2 > right1)
		return false;

	if (top1 < top2 && bot1 > bot2 && left1 < left2 && right1 > right2)
		return true;
	//================

	//Same row
	if ((OBJ1.Get_top() < ((OBJ2.Get_top() + OBJ2.Get_bottom()) / 2) && ((OBJ2.Get_top() + OBJ2.Get_bottom()) / 2) < OBJ1.Get_bottom()) || (OBJ2.Get_top() < ((OBJ1.Get_top() + OBJ1.Get_bottom()) / 2) && ((OBJ1.Get_top() + OBJ1.Get_bottom()) / 2) < OBJ2.Get_bottom()))
	{
		bool x = (OBJ1.Get_top() < ((OBJ2.Get_top() + OBJ2.Get_bottom()) / 2) && ((OBJ2.Get_top() + OBJ2.Get_bottom()) / 2) < OBJ1.Get_bottom());

		bool y = (OBJ2.Get_top() < ((OBJ1.Get_top() + OBJ1.Get_bottom()) / 2) && ((OBJ1.Get_top() + OBJ1.Get_bottom()) / 2) < OBJ2.Get_bottom());

		if (OBJ1.Get_right() < OBJ2.Get_left())
			return true;
		if (OBJ2.Get_right() < OBJ1.Get_left())
			return false;
	}
	//========

	// Overlap on oY
	if (!(OBJ1.Get_top() > OBJ2.Get_bottom() || OBJ2.Get_top() > OBJ1.Get_bottom())) {
		return OBJ1.Get_top() < OBJ2.Get_top();
	}
	//Different rows
	else {
		if (OBJ1.Get_bottom() < OBJ2.Get_top())
			return true;
		else
			return false;
	}
	//==============	
}
