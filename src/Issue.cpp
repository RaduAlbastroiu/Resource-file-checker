//============================
//Issues class cpp definition:
//============================

#include "stdafx.h"
#include "Issue.h"
#include "widget.h"



// convert int to wstring
wstring Issue::int_to_wstring(int x)
{
	wstring number = to_wstring(x);
	return number;
}

