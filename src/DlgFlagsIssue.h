#pragma once
#include "stdafx.h"
#include "widget.h"
#include "Issue.h"
#include "DlgFlags.h"

class DlgFlagsIssue : public Issue {
	
	public:

		//
		DlgFlagsIssue(vector < pair<DlgFlags::action, DlgFlags::flag> > suggestionsForFix);
		virtual vector<wstring> Create_message() override;

	private:

		//vector of suggestion for fixes
		vector < pair<DlgFlags::action, DlgFlags::flag> > suggestions;

		// converts the element from the enumeration "action" to wstring
		wstring actionToWstring(DlgFlags::action chosenAction);

		// converts the element from the enumeration "flag" to wstring
		wstring flagToWstring(DlgFlags::flag chosenFlag);
};