#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "padding.h"

#define MAX_COMPARISON_DISTANCE 50

class padding_first_layer : public padding
{

public:

	// constructor 
	padding_first_layer(vector<widget> &dialog_elements);

	void check_padding_first_layer(Accumulator &Accumulate_Issues);


protected:

	// all widget from this dialog
	vector<widget> &dialogElements;

	map < int, vector<widget>> Layer;

	
	// Have a map where the key is the column and each element of the map is a vector of
	// widgets left aligned to that column (key).
	// For each layer a map will be created.
	map<int, vector<widget>> create_Map(const vector<widget> &controllers);

	bool should_check(const widget &A, const widget &B);

	bool is_on_white_list(const widget &A, const widget &B);

		// returns true if the widgets are the same type
		bool same_type(const widget &A, const widget & B);

		// returns true if there is C in berween A and B
		bool in_between_vertically(const widget &A, const widget &B, const widget &C);

		// returns true if there is not a controller that is on the same line with both controllers
		bool on_the_sides(const widget &A, const widget &B, const widget &C);

		// returns true if the widgets are aligned each with another editext or drop down list
		bool horizontally_aligned_widgets(const widget &A, const widget &B);
			// if thhese controllers have the same mid line
			bool same_mid_line(const widget &A, const widget &B);

	// returns true if widgetB is contained in widgetA
	bool overlapped_controllers(const widget &OBJ1, const widget OBJ2);

};


