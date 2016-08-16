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
bool sorting::comp(const widget &first, const widget &second)
{
	int middle1 = (first.Get_top()  + first.Get_bottom())  / 2;
	int middle2 = (second.Get_top() + second.Get_bottom()) / 2;

	// If an object contains another then that object should be put before the other one 
	if (second.contains(first))
		return false;

	if (first.contains(second))
		return true;

	// Order them from left to right if the middle of an object intersects the middle of the other one
	if ((first.Get_top()  <= middle2 && middle2 <= first.Get_bottom()) || 
		(second.Get_top() <= middle1 && middle1 <= second.Get_bottom()))
	{
		return first.Get_left() < second.Get_left();
	}

	// Otherwise order them by top
	return first.Get_top() < second.Get_top();
}
