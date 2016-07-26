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

	for (auto iter : Layer)
	{
		for (int i = 0; i < iter.second.size(); i++)
		{
			for (int j = 0; j < iter.second.size(); j++)
			{
				if (should_check(iter.second[i], iter.second[j]))
				{
					int expected = getExpectedVerticalDistance(getKey(iter.second[i]), getKey(iter.second[j]));
					int real = computeVerticalDistance(iter.second[i], iter.second[j]);

					if ( real != expected )
					{
						unique_ptr<Issue> pointer = make_unique< padding_issue_horizontally >(iter.second[i], iter.second[j], expected-real);
						Accumulate_Issues.push_issue(move(pointer));
					}
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

bool padding_first_layer::should_check(widget &A, widget &B)
{
	if (A.Is_browse_button() || B.Is_browse_button())
		return false;

	if (A.Get_deep() > 1 || B.Get_deep() > 1)
		return false;

	return true;
}

int padding_first_layer::expected_vertical_distance(const widget & A, const widget & B)
{
	int expected = getExpectedVerticalDistance(getKey(B), getKey(B));
	int found = computeVerticalDistance(A, B);

	if (expected == found)
		return expected;
}

