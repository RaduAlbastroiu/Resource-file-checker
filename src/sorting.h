#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"

class sorting : public Valid
{
	private:
		static bool comp(const widget &OBJ1, const widget &OBJ2);
		void repair_sort(vector<widget> &controllers);

	public:
		bool valid = true;

		void check_sorting(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers);

};