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

	Layer = createMap(dialogElements);

	for (auto &iter : Layer)
	{
		sort(iter.second.begin(), iter.second.end(),
			[](const widget &A, const widget &B) { return A.Get_top() < B.Get_top(); });

		for (int i = 0; i < iter.second.size() - 1; i++)
		{
			if (should_check(iter.second[i], iter.second[i + 1]))
			{
				int expected = getExpectedVerticalDistance(getKey(iter.second[i]), getKey(iter.second[i+1]));
				int real = computeVerticalDistance(iter.second[i], iter.second[i+1]);
				
				if (expected_vertical_distance(iter.second[i], iter.second[i + 1]) &&
					same_type(iter.second[i],iter.second[i+1]))
				{
					nrissues_padding_vertically++;

					unique_ptr<Issue> pointer = make_unique< padding_issue_horizontally >(iter.second[i], iter.second[i + 1], expected - real);

					Accumulate_Issues.push_issue(move(pointer));
				}
			}
		}
	}
}


map<int, vector<widget>> padding_first_layer::createMap(const vector<widget> &controllers)
{
	map<int, vector<widget>> leftColumns;

	/*
	Put each widget in a bucket corresponding to its left column
	*/
	for (const auto &controller : controllers) {

		//Browse buttons, pushbuttons, defpushbuttons and groupboxes are ignored.
		if (!controller.Is_browse_button() && !controller.isPushButton() && !controller.isDefPushButton() && !controller.Is_transparent()) {
			int key = controller.Get_left();
			leftColumns[key].push_back(controller);
		}
	}

	/*
	Iterate through the elements of the map
	*/
	for (auto &leftColumn : leftColumns) {

		//Sort each of the vectors in the map increasingly based on the top of the contained controllers.
		sort(leftColumn.second.begin(), leftColumn.second.end(),
			[](const widget &w1, const widget &w2) {
			return w1.Get_top() < w2.Get_top();
		});
	}

	return leftColumns;
}

bool padding_first_layer::should_check(const widget &A, const widget &B)
{
	if (A.Is_browse_button() || B.Is_browse_button())
		return false;

	if (A.Get_deep() > 1 || B.Get_deep() > 1)
		return false;

	return true;
}

bool padding_first_layer::expected_vertical_distance(const widget & A, const widget & B)
{
	int expected = getExpectedVerticalDistance(getKey(B), getKey(B));
	int found = computeVerticalDistance(A, B);

	// if the distance is good
	if (expected == found)
		return false;
	
	// if the distance is too big
	if (found > MAX_COMPARISON_DISTANCE)
		return false;

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
			continue;

		return true;

	}
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
		return true;

	return false;
}

