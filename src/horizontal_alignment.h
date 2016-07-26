#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"

// 
#define horizontal_distance 100
#define max_comparison_height 15


class horizontal_alignment : public Valid
{
	private:
		bool if_not_aligned(widget* OBJ1, widget* OBJ2);

		bool if_cross_line(widget* OBJ1, widget* OBJ2, vector<widget> &Dialog_controllers);
		bool if_close(widget* OBJ1, widget* OBJ2);
		bool if_same_size(widget* OBJ1, widget* OBJ2);

	public:
		
		void check_rows(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers);
};