#pragma once
//=========================
//Accumulator class header:
//=========================

#include "stdafx.h"
#include "Issue.h"

class Accumulator
{
	public:
		//Add element
		void push_issue(unique_ptr <Issue> obj );

		//Info about vector
		vector< unique_ptr <Issue> >::const_iterator Begin_Issues();
		vector< unique_ptr <Issue> >::const_iterator End_Issues();
		size_t Get_size();
	
	private:
		vector< unique_ptr <Issue> > Issues_container;
};
