#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "DialogMargins.h"
#include "Dialog_box.h"
#include "DialogLeftMarginIssue.h"
#include "DialogRightMarginIssue.h"
#include "DialogTopMarginIssue.h"
#include "DialogBottomMarginIssue.h"

#include <numeric>
#include <iterator>

DialogMargins::DialogMargins(const Dialog_box &currentDialog, const vector<widget> &dialogWidgets):
	dialog(currentDialog)
{
	copy_if(dialogWidgets.begin(), dialogWidgets.end(), back_inserter(topLayerElems),
		[&](const widget &elem) {
			return dialog.containsWidget(elem) && elem.Get_father_pointer() == PTR_DIALOG;
	});
}

widget DialogMargins::getLeftmost() {
	return *min_element(topLayerElems.begin(), topLayerElems.end(), 
		[](const widget &w1, const widget &w2) {
			return w1.Get_left() < w2.Get_left();
	});
}

widget DialogMargins::getRightmost() {
	return *max_element(topLayerElems.begin(), topLayerElems.end(),
		[](const widget &w1, const widget &w2) {
			return w1.Get_right() < w2.Get_right();
	});
}

widget DialogMargins::getUppermost() {
	return *min_element(topLayerElems.begin(), topLayerElems.end(), 
		[](const widget &w1, const widget &w2) {
			return w1.Get_top() < w2.Get_top();
	});
}

widget DialogMargins::getLowermost() {
	return *max_element(topLayerElems.begin(), topLayerElems.end(), 
		[](const widget &w1, const widget &w2) {
			return w1.Get_bottom() < w2.Get_bottom();
	});
}

int DialogMargins::getCurrentLeftMargin() {
	return getLeftmost().Get_left();
}

int DialogMargins::getCurrentRightMargin() {
	int margin = dialog.Get_width() - getRightmost().Get_right();
	
	return dialog.hasFlagWS_SCROLL() ? margin - SCROLL_SIZE : margin;
}

int DialogMargins::getCurrentTopMargin() {
	return getUppermost().Get_top();
}

int DialogMargins::getCurrentBottomMargin() {
	int margin = dialog.Get_height() - getLowermost().Get_bottom();

	return dialog.hasFlagWS_SCROLL() ? margin - SCROLL_SIZE : margin;
}

bool DialogMargins::areOKMargins(int leftMargin, int rightMargin, int topMargin, int bottomMargin) {
	return (leftMargin == FRAME_LEFT_MARGIN && rightMargin  == FRAME_RIGHT_MARGIN &&
			topMargin  >= FRAME_TOP_MARGIN  && bottomMargin >= FRAME_BOTTOM_MARGIN)
			||
		   (leftMargin == MODAL_LEFT_MARGIN && rightMargin  == MODAL_RIGHT_MARGIN &&
			topMargin  == MODAL_TOP_MARGIN  && bottomMargin == MODAL_BOTTOM_MARGIN);
}

void DialogMargins::validateLeftMargin(const int &currentMargin, Accumulator &issuesAccumulator) {
	int expectedMargin = dialog.isFrame() ? FRAME_LEFT_MARGIN : MODAL_LEFT_MARGIN;

	if (expectedMargin != currentMargin) {
		unique_ptr < Issue > pointer = make_unique < DialogLeftMarginIssue >(currentMargin, expectedMargin);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}
}

void DialogMargins::validateRightMargin(const int &currentMargin, Accumulator &issuesAccumulator) {
	int expectedMargin = dialog.isFrame() ? FRAME_RIGHT_MARGIN : MODAL_RIGHT_MARGIN;

	if (expectedMargin != currentMargin) {
		unique_ptr < Issue > pointer = make_unique < DialogRightMarginIssue >(currentMargin, expectedMargin);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}
}

void DialogMargins::validateTopMargin(const int &currentMargin, Accumulator &issuesAccumulator) {
	
	if (dialog.isFrame()) {
		if (currentMargin < FRAME_TOP_MARGIN) {
			unique_ptr < Issue > pointer = make_unique < DialogTopMarginIssue >(currentMargin, FRAME_TOP_MARGIN);
			nrIssuesDialogMargins++;
			issuesAccumulator.push_issue(move(pointer));
		}
	}
	else {
		if (currentMargin != MODAL_TOP_MARGIN) {
			unique_ptr < Issue > pointer = make_unique < DialogTopMarginIssue >(currentMargin, MODAL_TOP_MARGIN);
			nrIssuesDialogMargins++;
			issuesAccumulator.push_issue(move(pointer));
		}
	}
}

void DialogMargins::validateBttomMargin(const int &currentMargin, Accumulator &issuesAccumulator) {
	if (dialog.isFrame()) {
		if (currentMargin < FRAME_BOTTOM_MARGIN) {
			unique_ptr < Issue > pointer = make_unique < DialogBottomMarginIssue >(currentMargin, FRAME_BOTTOM_MARGIN);
			nrIssuesDialogMargins++;
			issuesAccumulator.push_issue(move(pointer));
		}
	}
	else {
		if (currentMargin != MODAL_BOTTOM_MARGIN) {
			unique_ptr < Issue > pointer = make_unique < DialogBottomMarginIssue >(currentMargin, MODAL_BOTTOM_MARGIN);
			nrIssuesDialogMargins++;
			issuesAccumulator.push_issue(move(pointer));
		}
	}
}

void DialogMargins::validate(Accumulator &issuesAccumulator) {

	// there are dialogs with no elements
	if (topLayerElems.empty()) {
		return;
	}

	// the current margins of the dialog
	int currentLeftMargin   = getCurrentLeftMargin();
	int currentRightMargin  = getCurrentRightMargin();
	int currentTopMargin    = getCurrentTopMargin();
	int currentBottomMargin = getCurrentBottomMargin();

	if (areOKMargins(currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin))
		return;

	// validations for each margin
	validateLeftMargin(currentLeftMargin, issuesAccumulator);
	validateRightMargin(currentRightMargin, issuesAccumulator);
	validateTopMargin(currentTopMargin, issuesAccumulator);
	validateBttomMargin(currentBottomMargin, issuesAccumulator);
}