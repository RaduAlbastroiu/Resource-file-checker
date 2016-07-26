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
	this->valid = true;
	int i, j;
	auto n = Dialog_controllers.size();
	vector<widget> Dialog_controllers_sort;

	for (i = 1; i < n; i++)
	{
		if (comp(Dialog_controllers[i - 1], Dialog_controllers[i]) == false)
		{
			this->valid = false;

			for (j = 0; j < n; j++)
			{
				Dialog_controllers_sort.push_back(Dialog_controllers[j]);
			}
			//sorting
			std::sort(Dialog_controllers_sort.begin(), Dialog_controllers_sort.end(), comp);

			this->repair_sort(Dialog_controllers_sort);

			for (j = 0; j < Dialog_controllers.size(); j++)
			{
				if (Dialog_controllers[j] != Dialog_controllers_sort[j])
				{
					//increase the nr of issues for this type
					nrissues_sort++;

					//create obj
					unique_ptr < Issue > pointer = make_unique < sorting_issue >(Dialog_controllers_sort);

					Accumulate_Issues.push_issue(move(pointer));

					return;
				}
			}
		}
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
	if ((OBJ1.Get_top() < ((OBJ2.Get_top() + OBJ2.Get_bottom()) / 2) && ((OBJ2.Get_top() + OBJ2.Get_bottom()) / 2) < OBJ1.Get_bottom()) || (OBJ2.Get_top() < ((OBJ1.Get_top() + OBJ1.Get_bottom()) / 2) && ((OBJ1.Get_top() + OBJ2.Get_bottom()) / 2) < OBJ2.Get_bottom()))
	{
		if (OBJ1.Get_right() < OBJ2.Get_left())
			return true;
		if (OBJ2.Get_right() < OBJ1.Get_left())
			return false;
	}
	//========

	//Different rows
	if (OBJ1.Get_bottom() < OBJ2.Get_top())
		return true;
	else
		return false;
	//==============
}
