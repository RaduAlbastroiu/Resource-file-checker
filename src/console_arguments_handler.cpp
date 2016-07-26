#include "stdafx.h"
#include "console_arguments_handler.h"
#include <string.h>
#include <exception>

wstring console_arguments_handler::char_array_to_wstring(char *arr)
{
	wstring returned_wstring = L"";

	for (int index = 0; index < strlen(arr); index++)
	{
		returned_wstring += wchar_t(arr[index]);
	}

	return returned_wstring;
}

string console_arguments_handler::char_array_to_string(char *arr)
{
	string returned_string = "";

	for (int index = 0; index < strlen(arr); index++)
	{
		returned_string += arr[index];
	}

	return returned_string;
}

vector<wstring> console_arguments_handler::get_requested_dialogs()
{
	return requested_dialogs;
}

vector<wstring> console_arguments_handler::get_requested_validators()
{
	return requested_validators;
}

void console_arguments_handler::help(const int &current_command, const string &current_argument)
{
	//check if help was requested
	if (current_command != help_command) {

		//if not, then an error occurred
		cout << "Error: ";

		//unknown command or no file given
		//if the current command is not "-d" and is not "-f"
		if (current_command != dialog_command && current_command != file_name_command)
		{
			//validator commands don't get here, so most probably there is an unknown command
			if (arguments_parsed == false)
			{
				cout << "Unknown command: " << current_argument << "\n\n";
			}
			//however, if no arguments are given, then the error below must be printed 
			//(has a higher priority)
			else
			{
				cout << "No file given\n\n";
			}
		}
		//no commands given
		else if (total_commands == 0)
		{
			cout << "The first argument must be a command\n\n";
		}
		//all arguments parsed but no file given -> error
		else if (file_given == false)
		{
			cout << "No file given\n\n";
		}
	}
	cout << "Usage: Resource File Checker [options]\n\n";

	cout << "Options:\n";
	cout << "-f, --file NAME\t\t" << "Resource file name\n";
	cout << "-d, --dialog dialog_ID\t" << "Validation of given dialogs\n\n";

	cout << "Validation customization:\n\n";
	cout << "-dd\t" << "runs the dialog dimensions validator\n";
	cout << "-ol\t" << "runs the overlapping validator\n";
	cout << "-ca\t" << "runs the column alignment validator\n";
	cout << "-ha\t" << "runs the horizontal alignment validator\n";
	cout << "-st\t" << "runs the standard dimensions validator\n";
	cout << "-pd\t" << "runs the padding validator\n";
	cout << "-zo\t" << "runs the z-order validator\n\n";

	cout << "NOTE: If the '-d' command is not given, all the dialogs will be validated.\n";
	cout << "NOTE: If none of the validator commands are given, all the validators will run.\n";
	
	
}

void console_arguments_handler::choose_action(int current_command, char *current_arg_char, const wstring &current_argument_wstring)
{
	vector<wstring>::iterator found;

	switch (current_command)
	{
		case file_name_command:
			set_file_name(char_array_to_string(current_arg_char));
			file_given = true;
			break;

		case dialog_command:
			requested_dialogs.push_back(current_argument_wstring);
			break;

		default:
			good = false;
			help(current_command, char_array_to_string(current_arg_char));
	}
}

void console_arguments_handler::append_unique_validator(const wstring &current_argument)
{
	if (find(requested_validators.begin(), requested_validators.end(), current_argument) != requested_validators.end())
	{
		return;
	}

	requested_validators.push_back(current_argument);
}

console_arguments_handler::console_arguments_handler(int argc, char **argv)
{	

	//To support the case where the first argument is not a command
	//This is an error
	int current_command = unknown_command;
	int index;

	//Go through the arguments while errors don't occur
	for (index = 1; index < argc && good; index++)
	{
		wstring current_argument = char_array_to_wstring(argv[index]);

		//Check if the current argument is a command
		//If so, make it the current command
		if (current_argument == L"-f" || current_argument == L"--file") 
		{
			total_commands++;
			current_command = file_name_command;
			continue;
		}
		else if (current_argument == L"-d" || current_argument == L"--dialog")
		{
			total_commands++;
			current_command = dialog_command;
			continue;
		}
		else if (find(validator_list.begin(), validator_list.end(), current_argument) != validator_list.end())
		{
			total_commands++;
			current_command = validator_command;	
			append_unique_validator(current_argument);
			continue;
		}
		else if (current_argument == L"-h") 
		{
			user_help_requested = true;
			current_command = help_command;
			help(current_command, char_array_to_string(argv[index]));
		}
		else {
			choose_action(current_command, argv[index], current_argument);
		}
	}

	if (index == argc)
	{
		arguments_parsed = true;
	}

	//If commands were given but the input file was not specified
	//Make error
	if (good && file_given == false && user_help_requested == false)
	{
		help(current_command, char_array_to_string(argv[argc-1]));
	}
	

	//not requesting any validator means running all of the validators
	if (requested_validators.empty())
	{
		requested_validators = validator_list;
	}

}