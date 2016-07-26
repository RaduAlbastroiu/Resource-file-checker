#pragma once
#define unknown_command 0
#define file_name_command 1
#define dialog_command 2
#define validator_command 3
#define help_command 4

class console_arguments_handler {
	private:
		//the vector of requested dialogs
		vector<wstring> requested_dialogs;

		//the vector of requested validators
		vector<wstring> requested_validators;

		//contains the name of the file
		string file_name = "";

		bool file_given = false;
		bool good = true;
		bool user_help_requested = false;

		//is true when all the console arguments were parsed
		bool arguments_parsed = false;

		//counts the total number of commands
		int total_commands = 0;
		
		
		//list of validator definitions
		vector<wstring> validator_list{ L"-dd", L"-ol", L"-ca", L"-ha", L"-sd", L"-pd", L"-dm", L"-df", L"-zo" };


		//conversion from a character array to wstring
		wstring char_array_to_wstring(char *arr);
		//conversion from character array to string
		string char_array_to_string(char *arr);

		//appends a validator if it is not already added
		void append_unique_validator(const wstring &current_argument);

	public:
		//finds the requested dialogs and requested dialogs
		//given as console arguments
		console_arguments_handler(int argc, char **argv);
		void choose_action(int current_command, char *current_arg_char, const wstring &current_argument_wstring);

		vector<wstring> get_requested_dialogs();
		vector<wstring> get_requested_validators();

		string get_file_name() { return file_name; }
		void set_file_name(string name) { file_name = name; }

		//displaying help for the user
		void help(const int &current_command, const string &current_argument);

		//returns true if no errors in parsing the console arguments occur
		bool is_good() { return good; }

		//returns true if the name of the file was given as argument
		bool is_file_given() { return file_given; }
		
};