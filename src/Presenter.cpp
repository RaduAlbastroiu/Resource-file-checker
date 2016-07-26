//========================
//Presenter class defined:
//========================

#include "stdafx.h"
#include "Presenter.h"
#include "Accumulator.h"
#include "Issue.h"
#include "Message_output.h"

void Presenter::take_it(vector< unique_ptr <Issue> > ::const_iterator start, size_t size)
{
	int i;
	Message_output message;
	//test
	vector<wstring> stringul;
	
	if (size == 0)
	{
		return;
	}

	auto n = size;

	for (i = 0; i < n; i++)
	{
		stringul = start[i]->Create_message();
		message.Message_out(stringul);
	}
	return;
}