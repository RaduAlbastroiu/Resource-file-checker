#pragma once
//=======================
//Presenter class header:
//=======================

#include "stdafx.h"
#include "Accumulator.h"
#include "Issue.h"
#include "Message_output.h"


class Presenter
{
	private:
		void take_it(vector< unique_ptr <Issue> > ::const_iterator start, size_t size);
	
	public:
		void take_issues(vector< unique_ptr <Issue> > ::const_iterator start, size_t size)
		{
			take_it(start, size);
		}
};