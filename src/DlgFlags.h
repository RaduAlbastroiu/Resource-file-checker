#pragma once
#include "stdafx.h"
#include "Valid.h"
#include "Dialog_box.h"
#include "Accumulator.h"

class DlgFlags : public Valid {
	
	public:

		// flag enumeration
		enum flag {
			FLAG_WS_CHILD,
			FLAG_WS_SYSMENU,
			FLAG_WS_CAPTION,
			FLAG_WS_BORDER,
			FLAG_WS_POPUP,
			FLAG_WS_THICKFRAME,
			FLAG_DS_MODALFRAME
		};

		// action enumeration ( addition or removal of flags )
		enum action {
			ADD,
			REMOVE
		};

		// constructor for creating a refrence to the dialog
		DlgFlags(const Dialog_box &dlg);

		// dialog flags validation
		void validate(Accumulator &issueAccumulator);

	private:
		// refrence of the dialog
		const Dialog_box &dialog;

		// function for creating an a DlgFlagsIssue
		unique_ptr<Issue> createIssue(const flag &chosenFlag, const action &chosenAction);
};