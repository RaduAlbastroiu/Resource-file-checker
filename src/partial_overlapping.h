#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"


class partial_overlapping : public Valid
{
	private:
		vector<widget> elements_ol;
		
		// returns true if the two widgets have overlapping
		bool overlapping_check(const widget &OBJ1, const widget &OBJ2);
		
		// returns true if the two widgets have overlapping
		bool overlapping_ordinary_widgets(const widget &OBJ1, const widget &OBJ2);

			// return true if there is overlapping between A and B
			bool widgetA_overlapping_widgetB(const widget &OBJ1, const widget &OBJ2);
			// return false if the elements are not stacked else return true
			bool overlapping_stacked_widgets(const widget &OBJ1, const widget &OBJ2);
		
		// returns true if the two widgets have overlapping
		bool overlapping_transparent_groupbox(const widget &OBJ1, const widget &OBJ2);

		// returns true if widgetB is contained in widgetA
		bool widgetA_contains_widgetB(const widget &OBJ1, const widget OBJ2);

		
	public:

		void check_partial_overlapping(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers);
};
