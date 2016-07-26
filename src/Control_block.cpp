//========================
//Control block class cpp:
//========================

#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Control_block.h"
#include "Valid.h"
#include "Message_output.h"
#include "Accumulator.h"
#include "Presenter.h"
#include "Parsare_Input.h"
#include "string.h"

Control_block::Control_block(const vector<wstring> &dialogs, const vector<wstring> &validators)
{
	requested_dialogs = dialogs;
	requested_validators = validators;

	tested_dialogs_customization = !requested_dialogs.empty();
	validation_customization = !requested_validators.empty();

	Valid::set_requested_validators(requested_validators);
	Valid::set_customized_validation(validation_customization);
}

bool Control_block::Should_be_tested(const wstring &ID)
{
	//returns true if the user gave as arguments a list of dialogs and
	//the ID is found in that list or if the user gave no list
	return tested_dialogs_customization == false || (tested_dialogs_customization == true && find(requested_dialogs.begin(), requested_dialogs.end(), ID) != requested_dialogs.end());
}

void Control_block::Do_The_job(string input_file)
{
	int i = 0;
	int count = 0;
	Parsare Read(input_file, requested_dialogs);
	Message_output message;

	//if the file is not found in the given directory display a message
	if (input_file != "" && !Read.Is_open())
	{
		cout << "Input file could not be found\n\n";
		return;
	}

	Read.Skip_first();
	
	if (Read.Is_open())
	{
		for (; Read.good() && Read.keep_reading(); i++)
		{
			Accumulator Issues_container;
			Dialog_box Dialog_obj(Read);
			
			while (Dialog_obj.Get_nr_elements() == 0 && Dialog_obj.Get_ID() != L"")
			{
				Dialog_box Dialog_ob(Read);
				Dialog_obj = Dialog_ob;
			}

			if (Dialog_obj.Get_nr_elements() > 0 && Read.good())
			{
				if (!Should_be_tested(Dialog_obj.Get_ID()))
					continue;

				Valid Validation_obj;
				Validation_obj.Get_issues(Dialog_obj, Issues_container);

				if (Issues_container.Get_size() > 0)
				{

					//counts how many dialogs have issues
					count++;
					message.Dialog_ID(Dialog_obj.Get_ID());
					message.New_line();
					Presenter present_obj;
					present_obj.take_issues(Issues_container.Begin_Issues(), Issues_container.Get_size());
					
					message.New_line(); 
					message.New_line();
					message.New_line();
					message.New_line();
				}
			}
			else
			{
				break;
			}
		}
		message.Final();
		cout << "\n  Number of dialogs with issues: " << count;
		message.New_line();
		message.New_line();
		message.Nr_issues_type(Valid());

	}
}