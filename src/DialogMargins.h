#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "Dialog_box.h"

#define PTR_DIALOG NULL

// margins for thick frames
#define FRAME_LEFT_MARGIN 20
#define FRAME_RIGHT_MARGIN 20
#define FRAME_TOP_MARGIN 20
#define FRAME_BOTTOM_MARGIN 20

// margins for modal frames
#define MODAL_LEFT_MARGIN 7
#define MODAL_RIGHT_MARGIN 7
#define MODAL_TOP_MARGIN 7
#define MODAL_BOTTOM_MARGIN 7

class DialogMargins : public Valid {
	public :
		DialogMargins(const Dialog_box &currentDialog, const vector<widget> &dialogWidgets);
		void validate(Accumulator &issuesAccumulator);


	private:
		// the dialog with its top layer elements
		Dialog_box dialog;
		vector<widget> topLayerElems;

		// functions for getting the leftmost / rightmost / uppermost / lowermost widget
		widget getLeftmost();
		widget getRightmost();
		widget getUppermost();
		widget getLowermost();

		// functions for getting the actual margins of the dialog
		int getCurrentLeftMargin();
		int getCurrentRightMargin();
		int getCurrentTopMargin();
		int getCurrentBottomMargin();

		// functions for validating each margin
		void validateLeftMargin(const int &currentMargin, Accumulator &issuesAccumulator);
		void validateRightMargin(const int &currentMargin, Accumulator &issuesAccumulator);
		void validateTopMargin(const int &currentMargin, Accumulator &issuesAccumulator);
		void validateBttomMargin(const int &currentMargin, Accumulator &issuesAccumulator);
};