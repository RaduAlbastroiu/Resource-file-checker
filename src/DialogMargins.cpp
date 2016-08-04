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
			// copy the elements which are in the dialog and not contained in groupboxes
			// browse buttons, transparent groupboxes and spinbuttons are ignored
			return dialog.containsWidget(elem) &&  elem.Get_father_pointer() == PTR_DIALOG &&
			  	   !elem.Is_browse_button()	   && !elem.Is_transparent() && !elem.isSpinButton();
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

	widget X = getRightmost();
	int margin = dialog.Get_width() - getRightmost().Get_right();
	
	return dialog.hasFlagWS_HSCROLL() ? margin - VSCROLL_SIZE : margin;
}

int DialogMargins::getCurrentTopMargin() {
	return getUppermost().Get_top();
}

int DialogMargins::getCurrentBottomMargin() {
	int margin = dialog.Get_height() - getLowermost().Get_bottom();

	return dialog.hasFlagWS_VSCROLL() ? margin - HSCROLL_SIZE : margin;
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

bool DialogMargins::hasAMargin0(const int &left, const int &right, const int &top, const int &bottom) {
	return (left == 0) || (right == 0) || (top == 0 )|| (bottom == 0);
}

void DialogMargins::checkMarginsForFrame(const int &left, const int &right, const int &top, const int &bottom) {

	leftMarginFrameOK	 = (left    == FRAME_LEFT_MARGIN);
	rightMarginFrameOK	 = (right	== FRAME_RIGHT_MARGIN);
	topMarginFrameOK	 = (top		>= FRAME_BOTTOM_MARGIN);

	// frame bottom margin does not matter so by assumption it will always
	// be respected
	bottomMarginFrameOK  = true;

}

void DialogMargins::checkMarginsForModal(const int &left, const int &right, const int &top, const int &bottom) {

	leftMarginModalOK		= (left		== MODAL_LEFT_MARGIN);
	rightMarginModalOK		= (right	== MODAL_RIGHT_MARGIN);
	topMarginModalOK		= (top		== MODAL_TOP_MARGIN);
	bottomMarginModalOK		= (bottom	== MODAL_BOTTOM_MARGIN);

}

bool DialogMargins::hasFramePriority() {
	/*
	int framePriority = (int)(leftMarginFrameOK + rightMarginFrameOK + topMarginFrameOK + bottomMarginFrameOK);
	int modalPriority = (int)(leftMarginModalOK + rightMarginModalOK + topMarginModalOK + bottomMarginModalOK);

	return framePriority > modalPriority;
	*/

	// try guiding by vertical margins ( left + right )
	if (leftMarginFrameOK + rightMarginFrameOK > leftMarginModalOK + rightMarginModalOK) {
		return true;
	}
	else if (leftMarginFrameOK + rightMarginFrameOK < leftMarginModalOK + rightMarginModalOK) {
		return false;
	}

	// there is one margin of a modal dialog and one of a frame dialog
	// need to guide by the top margin
	if (topMarginFrameOK) {
		return true;
	}
	else if (topMarginModalOK){
		return false;
	}

	// since bottom margin is not respected usually, it cannot be used for guiding
	// just treat the dialog as modal
	return true;
}

void DialogMargins::validateAsFrame(const int &left, const int &right, const int &top, const int &bottom, Accumulator &issuesAccumulator) {
	
	// validates each margin as a frame margin and pushes a specific issue

	if (!leftMarginFrameOK && left < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogLeftMarginIssue >(left, FRAME_LEFT_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}

	if (!rightMarginFrameOK && right < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogRightMarginIssue >(right, FRAME_RIGHT_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}

	if (!topMarginFrameOK && top < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogTopMarginIssue >(top, FRAME_TOP_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}

	if (!bottomMarginFrameOK && bottom < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogBottomMarginIssue >(bottom, FRAME_BOTTOM_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}
}

void DialogMargins::validateAsModal(const int &left, const int &right, const int &top, const int &bottom, Accumulator &issuesAccumulator) {
	
	// validates each margin as a modal margin and pushes a specific issue

	if (!leftMarginModalOK && left < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogLeftMarginIssue >(left, MODAL_LEFT_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}

	if (!rightMarginModalOK && right < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogRightMarginIssue >(right, MODAL_RIGHT_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}

	if (!topMarginModalOK && top < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogTopMarginIssue >(top, MODAL_TOP_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}

	if (!bottomMarginModalOK && bottom < IGNORED_MARGIN) {
		unique_ptr < Issue > pointer = make_unique < DialogBottomMarginIssue >(bottom, MODAL_BOTTOM_MARGIN);
		nrIssuesDialogMargins++;
		issuesAccumulator.push_issue(move(pointer));
	}
}

bool DialogMargins::noMarginsMatch() {
	return  leftMarginModalOK == false && rightMarginModalOK == false && topMarginModalOK == false && bottomMarginModalOK == false &&
			leftMarginFrameOK == false && rightMarginFrameOK == false && topMarginFrameOK == false;
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

	if (areOKMargins(currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin) ||
		hasAMargin0 (currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin)) {
		return;
	}

	// OLD IMPLEMENTATION (BASED ON FLAGS)
	// validations for each margin
	validateLeftMargin (currentLeftMargin,	 issuesAccumulator);
	validateRightMargin(currentRightMargin,	 issuesAccumulator);
	validateTopMargin  (currentTopMargin,	 issuesAccumulator);
	validateBttomMargin(currentBottomMargin, issuesAccumulator);

	// NEW IMPLEMENTATION FROM HERE ON ( BASED ON CURRENT MARGINS )
	/*
	checkMarginsForFrame(currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin);
	checkMarginsForModal(currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin);

	// margins respecting no criteria are skipped
	if (noMarginsMatch()) {
		return;
	}

	if (hasFramePriority()) {
		// validate the dialog as frame
		validateAsFrame(currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin, issuesAccumulator);
	}
	else {
		// validate the dialog as modal
		validateAsModal(currentLeftMargin, currentRightMargin, currentTopMargin, currentBottomMargin, issuesAccumulator);
	}
	*/
}