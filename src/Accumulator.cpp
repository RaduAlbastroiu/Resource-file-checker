//======================
//Accumulator class cpp:
//======================

#include "stdafx.h"
#include "Issue.h"
#include "Accumulator.h"

vector< unique_ptr <Issue> >::const_iterator Accumulator::Begin_Issues()
{
	return Issues_container.begin();
}

vector< unique_ptr <Issue> >::const_iterator Accumulator::End_Issues()
{
	return Issues_container.end();
}

size_t Accumulator::Get_size()
{
	return Issues_container.size();
}

void Accumulator::push_issue(unique_ptr <Issue> obj)
{
	//insert an issue in the container
	Issues_container.push_back(move(obj));
}