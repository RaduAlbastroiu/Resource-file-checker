#pragma once
#include "stdafx.h"
#include "widget.h"
#include "Issue.h"
#include "DlgFlags.h"

class DlgFlagsIssue : public Issue {
	
	public:

		DlgFlagsIssue(DlgFlags::flag chosenFlag, DlgFlags::action chosenAction);
		virtual vector<wstring> Create_message() override;

	private:

		// the action to be done ( add / remove a flag )
		wstring action;
		// the flag upon which the action will be performed
		wstring flag;

		// converts the element from the enumeration "action" to wstring
		wstring actionToWstring(DlgFlags::action chosenAction);

		// converts the element from the enumeration "flag" to wstring
		wstring flagToWstring(DlgFlags::flag chosenFlag);
};