
#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "padding.h"

class padding_for_min_distance : public padding
{

public:
	// constructor 
	padding_for_min_distance(vector<widget> &dialog_elements);

	void check_padding_for_min_distance(Accumulator &Accumulate_Issues);

protected:

	// keeps track of whether a widget was checked
	vector<bool> state;

	vector<widget> &dialogElements;

	//returns true if an element at a specific position was already checked
	bool wasChecked(const vector<widget>::iterator &elemIt) { return state[elemIt - dialogElements.begin()]; }
	bool wasChecked(const int &pos) { return state[pos]; }

	//set an element as checked
	void setChecked(const vector<widget>::iterator &elemIt) { state[elemIt - dialogElements.begin()] = CHECKED; }
	void setChecked(const int &pos) { state[pos] = CHECKED; }

	//gets the elements of an unchecked layer
	vector<widget> getNextLayerElements();

	//validates a layer both vertically and horizontally
	void validateLayer(const vector<widget> &layerElems, Accumulator &issueAccumulator);

	//validate a pair of widgets vertically
	void validatePairVertically(const widget &first, const widget &second, Accumulator &issueAccumulator);

	//validate a pair of widgets vertically
	void validatePairHorizontally(const widget &first, const widget &second, Accumulator &issueAccumulator);


};

