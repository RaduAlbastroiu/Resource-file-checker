#pragma once
//====================
//Issues class header:
//====================

#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"

class Issue
{
	protected:
		wstring int_to_wstring(int x);

	public:
		//virtual method call
		virtual vector <wstring> Create_message() = 0;
		
		//virtual destructor
		virtual ~Issue() { };
};

