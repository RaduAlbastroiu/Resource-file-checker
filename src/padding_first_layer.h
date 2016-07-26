#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "padding.h"

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

	/*
	Have a map where the key is the column and each element of the map is a vector of
	widgets left aligned to that column (key).
	For each layer a map will be created.
	*/
	map<int, vector<widget>> createMap(const vector<widget> &controllers);

};

