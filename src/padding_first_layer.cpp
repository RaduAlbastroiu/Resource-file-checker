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
#include "padding_first_layer.h"
#include "padding_issue_vertically.h"
#include "padding_issue_horizontally.h"
#include "padding_issue_top.h"
#include "padding_issue_bot.h"
#include "padding_issue_right.h"
#include "padding_issue_left.h"
#include "padding_issue_type_control.h"

// constructor
padding_first_layer::padding_first_layer(vector<widget>& dialog_elements)
	:dialogElements(dialog_elements)
{
}


// main method
void padding_first_layer::check_padding_first_layer(Accumulator & Accumulate_Issues)
{

	Layer = create_Map(dialogElements);

	Mij_line = create_Map_for_Mij_line(dialogElements);

	for (auto &iter : Layer)
	{
		for (int i = 0; i < iter.second.size(); i++)
		{
			for (int j = i + 1; j < iter.second.size(); j++)
			{
				if (should_check(iter.second[i], iter.second[j]))
				{
					int expected = getExpectedVerticalDistance(getKey(iter.second[i]), getKey(iter.second[j]));
					int real = computeVerticalDistance(iter.second[i], iter.second[j]);

					if (expected > 0 &&
					   (!is_on_white_list(iter.second[i], iter.second[j])) &&
						same_type(iter.second[i], iter.second[j]))
					{
						nrissues_padding_vertically++;

						unique_ptr<Issue> pointer = make_unique< padding_issue_vertically >(iter.second[i], iter.second[j], expected - real);

						Accumulate_Issues.push_issue(move(pointer));
					}
				}
			}
		}
	}
}


map<int, vector<widget>> padding_first_layer::create_Map(const vector<widget> &controllers)
{
	map<int, vector<widget>> leftColumns;

	
	// Put each widget in a bucket corresponding to its left column
	for (const auto &controller : controllers) {

		// Browse buttons, pushbuttons, defpushbuttons and groupboxes are ignored.
		if (!controller.Is_browse_button() && !controller.Is_transparent()) {
			int key = controller.Get_left();
			leftColumns[key].push_back(controller);
		}
	}

	
	// Iterate through the elements of the map
	for (auto &Column : leftColumns) {

		// Sort each of the vectors in the map increasingly based on the top of the contained controllers.
		sort(Column.second.begin(), Column.second.end(),
			[](const widget &w1, const widget &w2) {
			return w1.Get_top() < w2.Get_top();
		});
	}

	return leftColumns;
}

map<int, vector<widget>> padding_first_layer::create_Map_for_Mij_line(const vector<widget>& controllers)
{

	map<int, vector<widget>> MijLine;

	// Put each widget in a bucket corresponding to its left column
	for (const auto &controller : controllers) {

		// Browse buttons, pushbuttons, defpushbuttons and groupboxes are ignored.
		if (!controller.Is_browse_button() && !controller.Is_transparent()) 
		{
			int key = controller.Get_bottom() - ((controller.Get_bottom()-controller.Get_top())/2);

			MijLine[key].push_back(controller);
		}
	}


	// Iterate through the elements of the map
	for (auto &line : MijLine) {

		// Sort each of the vectors in the map increasingly based on the top of the contained controllers.
		sort(line.second.begin(), line.second.end(),
			[](const widget &w1, const widget &w2) 
			{
				return w1.Get_left() < w2.Get_left();
			});
	}

	return MijLine;
}

bool padding_first_layer::should_check(const widget &A, const widget &B)
{
	if (A.Is_transparent() || B.Is_transparent())
		return false;

	if (A.Is_browse_button() || B.Is_browse_button())
		return false;

	//if (A.Get_deep() > 1 || B.Get_deep() > 1)
		//return false;

	if(A.Get_father_pointer() != B.Get_father_pointer())
		return false;

	if (overlapped_controllers(A, B))
		return false;

	return true;
}

bool padding_first_layer::is_on_white_list(const widget & A, const widget & B)
{
	int expected = getExpectedVerticalDistance(getKey(A), getKey(B));
	int found = computeVerticalDistance(A, B);

	// if the distance is good
	if (expected == found)
		return true;

	if ((A.Is_checkbox() || A.Is_radio_button()) &&
		B.Is_checkbox() || B.Is_radio_button())
		if ((found >= expected) && (found <= expected + 3))
			return true;

	// if the distance is too big
	if (found > MAX_COMPARISON_DISTANCE)
		return true;

	for (auto const &iter : dialogElements)
	{
		if (iter.Get_top() == A.Get_top() &&
			iter.Get_bottom() == A.Get_bottom() &&
			iter.Get_left() == A.Get_left() &&
			iter.Get_right() == A.Get_right())
			continue;

		if (iter.Get_top() == B.Get_top() &&
			iter.Get_bottom() == B.Get_bottom() &&
			iter.Get_left() == B.Get_left() &&
			iter.Get_right() == B.Get_right())
			continue;

		if (in_between_vertically(A, B, iter))
			return true;
		
		if (iter.Get_type() == L"CONTROL" &&
			(A.isPushButton() || A.isDefPushButton()) &&
			(B.isPushButton() || B.isDefPushButton()))
		{
			if (on_the_sides(A, B, iter))
				return true;
		}

	}

	// returns true if the widgets are aligned each with another editext or drop down list
	if (horizontally_aligned_widgets(A, B))
		return true;

	return false;
}

bool padding_first_layer::same_type(const widget & A, const widget & B)
{
	// special case for defpushbutton and pushbutton
	if ((A.isDefPushButton() && B.isPushButton()) || (A.isPushButton() && B.isDefPushButton()))
		return true;

	if ((A.Is_drop_list() && B.isEditText()) || (A.isEditText() && B.Is_drop_list()))
		return true;

	return A.Get_type() == B.Get_type(); 
}

bool padding_first_layer::in_between_vertically(const widget &A, const widget &B, const widget &C)
{
	// creating the rectangle in between two widgets
	int top = (A.Get_bottom() < B.Get_bottom()) ? A.Get_bottom() : B.Get_bottom();
	int bot = (A.Get_top() > B.Get_top()) ? A.Get_top() : B.Get_top();
	int left = (A.Get_left() < B.Get_left()) ? A.Get_left() : B.Get_left();
	int right = (A.Get_right() > B.Get_right()) ? A.Get_right() : B.Get_right();

	int top_final = (C.Get_top() > top) ? C.Get_top() : top;
	int bot_final = (C.Get_bottom() < bot) ? C.Get_bottom() : bot;
	int left_final = (C.Get_left() > left) ? C.Get_left() : left;
	int right_final = (C.Get_right() < right) ? C.Get_right() : right;

	if ((bot_final - top_final > 0) && (right_final - left_final > 0)) 
		if(!overlapped_controllers(A,C))
			if(!overlapped_controllers(B, C))
				return true;

	return false;
}

bool padding_first_layer::on_the_sides(const widget & A, const widget & B, const widget & C)
{
	int min_top = A.Get_top() < B.Get_top() ? A.Get_top() : B.Get_top();
	int max_bot = A.Get_bottom() > B.Get_bottom() ? A.Get_bottom() : B.Get_bottom();
	
	if (C.Get_top() <= min_top &&
		C.Get_bottom() >= max_bot)
		return true;

	return false;
}

bool padding_first_layer::horizontally_aligned_widgets(const widget & A, const widget & B)
{
	int MAX = expected_distance_between_mids(A, B);

	// complexity n^2 it can be reduced but this later on
	for (auto &line_a : Mij_line[mid_line(A)])
	{
		if (line_a.Get_top() == A.Get_top() &&
			line_a.Get_bottom() == A.Get_bottom() &&
			line_a.Get_left() == A.Get_left() &&
			line_a.Get_right() == A.Get_right())
			continue;

		for (auto &line_b : Mij_line[mid_line(B)])
		{
			if (line_b.Get_top() == B.Get_top() &&
				line_b.Get_bottom() == B.Get_bottom() &&
				line_b.Get_left() == B.Get_left() &&
				line_b.Get_right() == B.Get_right())
				continue;

			if (same_vertical(line_a, line_b))
			{
				int dist = expected_distance_between_mids(line_a, line_b);
				if (dist == -1)
					continue;
				if (dist > MAX)
					MAX = dist;
			}
		}
	}

	if (MAX > expected_distance_between_mids(A, B))
		return true;

	return false;
}

int padding_first_layer::expected_distance_between_mids(const widget & A, const widget & B)
{
	int expected = getExpectedVerticalDistance(getKey(A), getKey(B));
	int dist_a;
	int dist_b;

	if (A.Get_bottom() < B.Get_top())
	{
		dist_a = A.Get_bottom() - mid_line(A);
		dist_b = mid_line(B) - B.Get_top();
		
		return dist_a + dist_b + expected;
	}
	if (B.Get_bottom() < A.Get_top())
	{
		dist_a = mid_line(A) - B.Get_top();
		dist_b = B.Get_bottom() - mid_line(B);

		return dist_a + dist_b + expected;
	}
	
	return -1;
}

bool padding_first_layer::same_vertical(const widget & A, const widget & B)
{

	if (B.Get_left() <= A.Get_left() && A.Get_left() <= B.Get_right())
		return true;

	if (A.Get_left() <= B.Get_left() && B.Get_left() <= A.Get_right())
		return true;

	return false;
}

// returns true if widgetB is contained in widgetA
bool padding_first_layer::overlapped_controllers(const widget & OBJ1, const widget OBJ2)
{
	// creating the rectangle in between two widgets
	int top = (OBJ1.Get_top()    > OBJ2.Get_top()) ? OBJ1.Get_top() : OBJ2.Get_top();
	int bot = (OBJ1.Get_bottom() < OBJ2.Get_bottom()) ? OBJ1.Get_bottom() : OBJ2.Get_bottom();
	int left = (OBJ1.Get_left()   > OBJ2.Get_left()) ? OBJ1.Get_left() : OBJ2.Get_left();
	int right = (OBJ1.Get_right()  < OBJ2.Get_right()) ? OBJ1.Get_right() : OBJ2.Get_right();

	if (bot - top > 0 && right - left > 0)
		return true;

	return false;
}