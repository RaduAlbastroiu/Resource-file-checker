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

// the size of scroll
#define VSCROLL_SIZE 11
#define HSCROLL_SIZE 10

class DialogMargins : public Valid {
	public :
		DialogMargins(const Dialog_box &currentDialog, const vector<widget> &dialogWidgets);
		void validate(Accumulator &issuesAccumulator);


	private:

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

		// returns true if the margins are ok, for either frame or modal dialog
		// it does not consider flags
		bool areOKMargins(int leftMargin, int rightMargin, int topMargin, int bottomMargin);

		// functions for validating each margin
		void validateLeftMargin(const int &currentMargin, Accumulator &issuesAccumulator);
		void validateRightMargin(const int &currentMargin, Accumulator &issuesAccumulator);
		void validateTopMargin(const int &currentMargin, Accumulator &issuesAccumulator);
		void validateBttomMargin(const int &currentMargin, Accumulator &issuesAccumulator);

		// returns true if a margin is 0
		bool hasAMargin0(const int &left, const int &right, const int &top, const int &bottom);

		// checks the margins for each type of dialog
		void checkMarginsForFrame(const int &left, const int &right, const int &top, const int &bottom);
		void checkMarginsForModal(const int &left, const int &right, const int &top, const int &bottom);

		// returns true if the number of margins of the dialog that respect the frame margins
		// is larger or equal than the ones that respect the modal margins
		bool hasFramePriority();

		// validates the dialog as a frame
		void validateAsFrame(const int &left, const int &right, const int &top, const int &bottom, Accumulator &issuesAccumulator);
		// validates the dilog as a modal
		void validateAsModal(const int &left, const int &right, const int &top, const int &bottom, Accumulator &issuesAccumulator);

		// the dialog with its top layer elements
		Dialog_box dialog;
		vector<widget> topLayerElems;

		// a variable will be true if the specific margin for frame is respected
		bool leftMarginFrameOK;
		bool rightMarginFrameOK;		
		bool topMarginFrameOK;
		bool bottomMarginFrameOK;
		
		// a variable will be true if the specific margin for modal is respected
		bool leftMarginModalOK;
		bool rightMarginModalOK;
		bool topMarginModalOK;
		bool bottomMarginModalOK;
};