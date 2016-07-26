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
