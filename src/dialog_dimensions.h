#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"

class dialog_dimensions : public Valid
{
	public:
		void check_dialog_dimensions(Dialog_box &Dialog, Accumulator &Accumulate_issues);
};
