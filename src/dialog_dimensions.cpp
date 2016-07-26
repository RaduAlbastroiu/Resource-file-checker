#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Valid.h"
#include "Accumulator.h"
#include "dialog_dimensions.h"
#include "dialog_dimensions_issue.h"

//dialog dimensions check for issues
void dialog_dimensions::check_dialog_dimensions(Dialog_box &Dialog, Accumulator &Accumulate_isssues)
{
	if (Dialog.Get_height() > dialog_height || Dialog.Get_width() > dialog_width)
	{
		unique_ptr<Issue> pointer = make_unique<dialog_dimensions_issue>(Dialog);

		Accumulate_isssues.push_issue(move(pointer));
	}
}