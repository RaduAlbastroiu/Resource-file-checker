#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "partial_overlapping.h"
#include "overlapping_issue.h"


//partial overlapping check for issues
void partial_overlapping::check_partial_overlapping(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers)
{
	auto n = Dialog_controllers.size();
	int i = 0;
	int j = 0;

	vector<widget> issue;

	//Search for issues
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{

			// no issue if one widget is pushbutton named "..."
			if (!(Dialog_controllers[i].Is_browse_button() || Dialog_controllers[j].Is_browse_button()))
			{
				
				// testing if the two widgets have overlapping
				if (overlapping_check(Dialog_controllers[i], Dialog_controllers[j]))
				{
					
					// increase the nr of issues for this type
					nrissues_partial_ol++;

					issue.push_back(Dialog_controllers[i]);
					issue.push_back(Dialog_controllers[j]);

					// create issue obj
					unique_ptr < Issue > pointer = make_unique < overlapping_issue >(issue);

					Accumulate_Issues.push_issue(move(pointer));

					issue.clear();
				}
			}
		}
	}
}

bool partial_overlapping::overlapping_check(const widget &OBJ1, const widget &OBJ2)
{
	// if one of the two widgets is a groupbox with no name
	if (OBJ1.Get_type() == L"GROUPBOX" && OBJ1.Get_name() == L"" ||
		OBJ2.Get_type() == L"GROUPBOX" && OBJ2.Get_name() == L"")

		return overlapping_transparent_groupbox(OBJ1, OBJ2);

	// if there are two ordinary widgets
	else
		
		return overlapping_ordinary_widgets(OBJ1, OBJ2);
	
}

// returns true if the two widgets have overlapping
bool partial_overlapping::overlapping_ordinary_widgets(const widget & OBJ1, const widget & OBJ2)
{
	
	// if the elements are stacked there are no more issues generated
	if (overlapping_stacked_widgets(OBJ1, OBJ2))
		return false;

	if (widgetA_overlapping_widgetB(OBJ1, OBJ2))
		return true;

	return false;
}

// return true if there is overlapping between A and B
bool partial_overlapping::widgetA_overlapping_widgetB(const widget & OBJ1, const widget & OBJ2)
{

	// creating the rectangle in between two widgets
	int top    = (OBJ1.Get_top()    > OBJ2.Get_top())    ? OBJ1.Get_top()    : OBJ2.Get_top();
	int bot    = (OBJ1.Get_bottom() < OBJ2.Get_bottom()) ? OBJ1.Get_bottom() : OBJ2.Get_bottom();
	int left   = (OBJ1.Get_left()   > OBJ2.Get_left())   ? OBJ1.Get_left()   : OBJ2.Get_left();
	int right  = (OBJ1.Get_right()  < OBJ2.Get_right())  ? OBJ1.Get_right()  : OBJ2.Get_right();

	if (top == OBJ1.Get_top() && left == OBJ1.Get_left() && right == OBJ1.Get_right() && bot == OBJ1.Get_bottom() ||
	   (top == OBJ2.Get_top() && left == OBJ2.Get_left() && right == OBJ2.Get_right() && bot == OBJ2.Get_bottom()))
		return false;

	if (bot - top > 0 && right - left > 0)
		return true;

	return false;
}

// return false if the elements are not stacked else return true
bool partial_overlapping::overlapping_stacked_widgets(const widget & OBJ1, const widget & OBJ2)
{
	// extracting only usefull data from widget 1
	int left1 = OBJ1.Get_left();
	int right1 = OBJ1.Get_right();
	int top1 = OBJ1.Get_top();
	int bot1 = OBJ1.Get_bottom();

	// extracting only usefull data from widget 2
	int left2 = OBJ2.Get_left();
	int right2 = OBJ2.Get_right();
	int top2 = OBJ2.Get_top();
	int bot2 = OBJ2.Get_bottom();


	// widget on top of other widget with three common margins don't generate issues
	if (widgetA_contains_widgetB(OBJ1, OBJ2) && widgetA_contains_widgetB(OBJ2, OBJ1))
	{
		if (left1 == left2 && right1 == right2)
		{
			if (top1 == top2 || bot1 == bot2)
				return true;
		}
	}
	return false;
}

// returns true if the two widgets have overlapping
bool partial_overlapping::overlapping_transparent_groupbox(const widget & OBJ1, const widget & OBJ2)
{
	if (OBJ1.contains_mid_of(OBJ2) && !widgetA_contains_widgetB(OBJ1, OBJ2) && !widgetA_contains_widgetB(OBJ2, OBJ1) ||
		OBJ2.contains_mid_of(OBJ1) && !widgetA_contains_widgetB(OBJ2, OBJ1) && !widgetA_contains_widgetB(OBJ1, OBJ2))
		return true;
	
	return false;
}

// returns true if widgetB is contained in widgetA
bool partial_overlapping::widgetA_contains_widgetB(const widget & OBJ1, const widget OBJ2)
{
	// if OBJ2 is out of OBJ1 
	if (OBJ2.Get_top() < OBJ1.Get_top() ||
		OBJ2.Get_left() < OBJ1.Get_left() ||
		OBJ2.Get_right() > OBJ1.Get_right() ||
		OBJ2.Get_bottom() > OBJ1.Get_bottom())
		return false;

	return true;
}