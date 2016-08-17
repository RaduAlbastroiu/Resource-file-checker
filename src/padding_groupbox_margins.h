
#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "padding.h"

#define Dialog_max_dimension 100000
#define Dialog_min_dimension 0
#define Dialog_top_min_margin 12
#define Dialog_top_max_margin 12
#define Dialog_left_min_margin 9
#define Dialog_left_max_margin 10
#define Dialog_rigt_min_margin 7
#define Dialog_right_max_margin 10
#define Dialog_bot_min_margin 7
#define Dialog_bot_max_margin 7


class padding_groupbox_margins : public padding
{
	
public:
	// constructor 
	padding_groupbox_margins(vector<widget> &dialog_elements);

	void check_padding_groupbox_margins(Accumulator &Accumulate_Issues);

private:

	vector<widget> Dialog_controllers;

	//groupbox validation
	//distance validation between the groupbox and the 
	//uppermost, lowermost, leftmost, rightmost controllers
	//for each not respected distance, an issue is pushed
	void valid_check_top_groupbox(const widget& father, Accumulator &Accumulate_Issues);
	void valid_check_bot_groupbox(const widget& father, Accumulator &Accumulate_Issues);
	void valid_check_left_groupbox(const widget& father, Accumulator &Accumulate_Issues);
	void valid_check_right_groupbox(const widget& father, Accumulator &Accumulate_Issues);

};