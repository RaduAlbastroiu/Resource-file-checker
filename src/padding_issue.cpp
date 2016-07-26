#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "padding_issue.h"

//padding issue constructor
padding_issue::padding_issue(wstring ID1, wstring ID2, wstring type1, wstring type2, int row1, int row2) :
	first{ ID1, type1, row1 },
	second{ ID2, type2, row2 }
{}