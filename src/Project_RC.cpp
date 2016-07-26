// Project_RC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Control_block.h"
#include "console_arguments_handler.h"

int main(int argc, char **argv)
{	
	DWORD start = ::GetTickCount();

	console_arguments_handler handler(argc, argv);

	//Go to validation if arguments are good
	if (handler.is_good()) {
		//All the job down here:
		Control_block DO(handler.get_requested_dialogs(), handler.get_requested_validators());
		DO.Check_All_Dialogs(handler.get_file_name());
		//
	}
	DWORD finish = ::GetTickCount();

	cout << "\n";
	cout << "  Time in seconds : " << double((finish - start))/1000;
	cout << "\n";

	return 0;
}