//=========================
//Read text and parsing it:
//=========================

#include "stdafx.h"
#include "Parsare_Input.h"
#include "widget.h"
#include "Message_output.h"
#include "Dialog_box.h"

//Open the file(contructor)
Parsare::Parsare(const string & aFilename, const vector<wstring> &requested_dialog_ids)
	: fin(aFilename),codepage(Codepage_ENG),current_row(0)
{
	bool cp = true;//if codepage is still necessary
	
	Get_encoding(aFilename, fin, cp);
	requested_dialogs = requested_dialog_ids;
	customized_output = !requested_dialogs.empty();

	if (cp)
	{
		string code_page = ws2s(Get_Codepage(aFilename));
		if (code_page != ".1252")
		{
			fin.imbue(std::locale(code_page));
		}
	}
}

void Parsare::Read_requested_dialogs()
{
	wcout << L"Please insert the dialog IDs. \nPress CTRL+Z and hit ENTER when finished:\n";

	wstring dialog_id;

	//while there are still dialog IDs given by the user
	while (wcin >> dialog_id) 
	{
		//push them in the container for later
		requested_dialogs.push_back(dialog_id);
	}

	//if the user has given dialog IDs, then the output is customized
	if (requested_dialogs.size())
		customized_output = true;

}

//Find and set the encoding of the input stream
void Parsare::Get_encoding(const string &aFilename, wifstream &fin, bool &code_page)
{
	ifstream f;
	f.open(aFilename, std::ios_base::binary);
	if (f.is_open())
	{
		char type[256];
		f.read(type, 256);

		char ucs2_b1 = 0xFFu;
		char ucs2_b2 = 0xFEu;
		char utf8_b1 = 0xEFu;
		char utf8_b2 = 0xBBu;
		char utf8_b3 = 0xBFu;

		if (type[0] == ucs2_b1 && type[1] == ucs2_b2)
		{
			utf16 = true;

			locale utf16_LE_locale(fin.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
			fin.imbue(utf16_LE_locale);

			code_page = false;
			return;
		}
		if (type[0] == ucs2_b2 && type[1] == ucs2_b1)
		{
			utf16 = true;

			locale utf16_BE_locale(locale(), new codecvt_utf16<wchar_t>);
			fin.imbue(utf16_BE_locale);
			
			code_page = false;
			return;
		}
		if (type[0] == utf8_b1 && type[1] == utf8_b2 && type[2] == utf8_b3)
		{
			fin.imbue(std::locale(fin.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
			code_page = false;
			return;
		}
	}

	return;
}

//Find and return the codepage
wstring Parsare::Get_Codepage(const string & aFilename)
{
	wifstream file(aFilename);
	if (!file.is_open())
		return wstring(L".1252");

	wstring Line;
	wstring result;

	while (!file.eof())
	{
		getline(file, Line);

		// empty line
		if (Line.size() <= 1)
			continue;

		// skip anything but macros
		if (L'#' != Line[0])
			continue;

		if (Line[13] == L'p' && Line[14] == L'a' && Line[15] == L'g' && Line[16] == L'e')
		{
			result = Line.substr(18);
			result.erase(result.begin() + 4, result.end());
			break;
		}
	}
	file.close();

	// no #pragma code_page()
	if (result.empty())
		return wstring(L".1252");

	return L"." + result;
}

string Parsare::ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

//Isopen
bool Parsare::Is_open() const
{
	return fin.is_open();
}

bool Parsare::good() const
{
	return fin.good();
}

//Skip just the first time first:
void Parsare::Skip_first()
{
	wstring Line;
	wstring dialog = L"// Dialog";
	int i;
	for (i=0; fin.good() ;++i)
	{
		Line = Read_Line(fin);
		
		if (dialog == Line)
			return;
	}

	return;
}

//Finds the dialog name and dimensions
wstring Parsare::find_dialog_IDnr(int &width, int &height, int &row)
{
	wstring ID;
	wstring line;
	unsigned count = 0;
	int i = 0;

	for (;;)
	{
		ID = Read_Line(fin);
		if (ID == L"/////////////////////////////////////////////////////////////////////////////")
		{
			wstring End = { L"" };
			return End;
		}
		if (iswalnum(ID[0]))
		{
			//Giving the row to the dialog
			row = this->Get_nr_line();

			for (i = 0; i < ID.size(); i++)
			{
				if (ID[i] == L',')
				{
					count++;
					if (count == 2)
					{
						i += 2;
						line = L"";

						//Parsing dialog width
						while (true)
						{
							line += ID[i];
							if (ID[i + 1] == wchar_t(','))
							{
								i = i + 2;
								break;
							}
							else
								i++;
						}
						width = this->char_to_int(line);
						
						//Parsing dialog heigh
						line = L"";
						i++;
						while (true)
						{
							line += ID[i];
							if (i == ID.size() - 1)
								break;
							if (ID[i + 1] == wchar_t(','))
							{
								i = i + 2;
								break;
							}
							else
								i++;
						}
						height = this->char_to_int(line);
					}
				}
			}

			//Parsing dialog name
			for (i = 0; i < ID.size(); i++)
				if (!(iswalnum(ID[i]) || ID[i] == L'_'))
				{
					ID.erase(ID.begin() + i, ID.end());
					break;
				}

			return ID;
		}
	}
	return ID;
}

//Skip each:
void Parsare::Skip_text(bool &valid, Dialog_box &dialog)
{
	bool ok = false;
	wstring Line;
	if (valid == true)
	{
		for (;;)
		{
			Line = Read_Line(fin);

			//sets the current dialog to be a thickframe
			dialog.setFlags(Line);
			

			if (L"/////////////////////////////////////////////////////////////////////////////" == Line)
			{
				valid = false;
			}
		
			if (L"BEGIN" == Line)
				return;
		}
	}
}
//=======

//Read one line
wstring Parsare::Read_Line(wistream &in)
{
	wstring Line;
	getline(fin, Line, wchar_t('\n'));

	if (utf16)
		Line.pop_back();

	current_row++;
	return Line;
}

/*takes all the controllers of an dialog
from the input and keeps them in a vector
of wstrings*/
bool Parsare::Take_controller(Dialog_box &dialog)
{
	wstring Lread;
	wstring Line;
	wstring lastLineRead;
	bool valid = true;

	this->Skip_text(valid, dialog);
	if (valid == false)
		return false;

	Lread = this->Read_Line(fin);

	if(Lread == L"END")
	{
		return false;
		this->Skip_text(valid, dialog);
		if (valid == false)
			return false;
		Lread = this->Read_Line(fin);
	}

	for (;;)
	{
		if (Lread == L"END")
		{
			if(Line.size() > 0)
				Controllers.push_back(std::make_pair(Line, current_row));
			break;
		}

		if (isalnum(Lread[5]))
		{
			if(Line.size()>0)
				Controllers.push_back(std::make_pair(Line, current_row));
			Line.erase();
			Line = Lread;
		}
		else
		{
			Line = Line + L' ' + Lread;
		}
		Lread = this->Read_Line(fin);
	}
	return true;
}

bool Parsare::Is_requested_dialog(const wstring &ID)
{
	//returns true if the user hasn't asked for any dialogs
	if (!customized_output)
		return true;

	//or if he did ask for some dialogs, and the current dialog is one of them
	auto found = find(requested_dialogs.begin(), requested_dialogs.end(), ID);

	//delete the found dialog from the list
	if (found != requested_dialogs.end()) {
		requested_dialogs.erase(found);
		return true;
	}

	return false;
}

//returns true if the reading of the file must be continued
bool Parsare::keep_reading() 
{
	
	//- not all the dialogs given by the user have been found
	//- the user hasn't asked for any specific dialogs

	return customized_output == false || customized_output == true && requested_dialogs.size();
}

//Create the entire dialog
vector<widget> Parsare::Dialog_read(Dialog_box &dialog)
{
	bool valid = true;
	vector<widget> rect_elements;

	valid = this->Take_controller(dialog);
	if (valid == false)
		return rect_elements;
	
	widget OBJ;
	int i = 0;
	auto n = Controllers.size();
	
	for (;i<n;i++)
	{
		//==============================

		OBJ = Parsare::Parsare_line(Controllers[i].first); //Afiseaza si linia controlerului
		OBJ.Change_row(Controllers[i].second-1);
		
		rect_elements.push_back(OBJ);
		//Construirea vectorului dialog
	}

	Controllers.clear();

	return rect_elements;
}

//Line -> widget
widget Parsare::Parsare_line(wstring &Line)
{
	widget OBJ;
	
	Parsare::Parsare_tip(Line, OBJ);
	Parsare::Parsare_tab(Line, OBJ);
	Parsare::drop_list_check(Line, OBJ);
	Parsare::Parsare_group(Line, OBJ);
	Parsare::Parsare_radio_button(Line, OBJ);
	Parsare::Parsare_transparent(Line, OBJ);
	Parsare::Parsare_check_box(Line, OBJ);
	Parsare::Parsare_spin_button(Line, OBJ);
	Parsare::Parsare_name(Line, OBJ);
	Parsare::Parsare_ID(Line, OBJ);
	Parsare::Parsare_Set_position(Line, OBJ);
	
	return OBJ;
}

void Parsare::Parsare_tip(wstring &Line, widget &OBJ)
{
	//=================
	//Parsarea tipului:
	int i = 0;
	while (Line[i] == ' ')
		i++;
	wstring tip = L"";
	for (; i < Line.size(); i++)
	{
		if (iswalpha(Line[i])) {
			tip += Line[i];
		}
		else
			break;
	}
	while (Line[i] == wchar_t(' '))
		i++;
	Line.erase(Line.begin(), Line.begin() + i);
	OBJ.Set_type(tip);
}
void Parsare::Parsare_tab(wstring &Line, widget &OBJ)
{
	bool val = false;
	val = Line.find(L"WS_TABSTOP") != wstring::npos;
	
	OBJ.Change_Tab_valid(val);

	//Parsarea Tab validitatii
}
void Parsare::Parsare_group(wstring &Line, widget &OBJ)
{
	bool val = false;
	
	val = Line.find(L"WS_GROUP") != wstring::npos;

	OBJ.Change_group(val);
}
void Parsare::Parsare_radio_button(wstring &Line, widget &OBJ)
{
	bool val = false;
	
	val = Line.find(L"BS_AUTORADIOBUTTON") != wstring::npos;

	OBJ.Set_radio_button(val);
}
void Parsare::Parsare_transparent(wstring &Line, widget &OBJ)
{
	bool val = false;

	val = Line.find(L"WS_EX_TRANSPARENT") != wstring::npos;

	OBJ.Set_transparent(val);
}
void Parsare::Parsare_check_box(wstring &Line, widget &OBJ)
{
	bool val = false;

	val = Line.find(L"BS_AUTOCHECKBOX") != wstring::npos;

	if (val == false)
		val = Line.find(L"BS_AUTO3STATE") != wstring::npos;

	OBJ.Set_checkbox(val);
}

void Parsare::Parsare_spin_button(wstring &Line, widget &OBJ) {

	bool spin = Line.find(L"UDS_ARROWKEYS") != wstring::npos;

	if (spin) {
		OBJ.setSpinButton();
	}
}

void Parsare::drop_list_check(const wstring &line, widget &control)
{
	if (line.find(L"CBS_DROPDOWN") != wstring::npos)
		control.Set_drop_list();
}

//Function for name parsing, if a name exists
void Parsare::Parsare_name(wstring &Line, widget &OBJ)
{
	//Names are always written between quotation marks, which at this step of
	//input parsing can be only on position 0

	//If the widget has a name
	if (Line[0] == L'\"') 
	{
		wstring name;

		//Compute the positions for the start and the end of the word
		int start_position = 0;
		int end_position = (int)(Line.find(L'\"', start_position + 1));

		//Copy the part of the string where the name is to the variable name
		copy(Line.begin() + start_position + 1, Line.begin() + end_position, back_inserter(name));

		//Set the name of the object to name
		OBJ.Set_name(name);
	}
}

void Parsare::Parsare_ID(wstring &Line, widget &OBJ)
{
	//=================
	//Parsarea ID:
	int i = 0;
	auto Line_length = Line.size();
	wstring ID = L"";
	bool ok;

	for (; i < Line_length; ++i)
		if (isalpha(Line[i]) || Line[i] == '"')
			break;

	if (Line[i] == L'"')
	{
		ok = true;
		i++;
		while (Line[i] != L',' || ok) 
		{
			if (Line[i] == L'"')
				ok = false;
			i++;
		}
		i++;
	}

	for (; i < Line_length; i++)
	{
		if (iswalnum(Line[i]) || Line[i] == L'_' || Line[i] == L' ')
			ID += Line[i];
		else
			break;
	}
	if (ID == L"")
		ID = L"UNNAMED";
	OBJ.Set_ID(ID);
	Line.erase(Line.begin(), Line.begin() + i);
}
void Parsare::Parsare_Set_position(wstring &Line, widget &OBJ)
{
	wstring line;
	int x, y;
	int height, width;
	int i;
	
	i = 0;

	while (Line[i] != wchar_t(',') || Line[i + 1] <wchar_t('0') || Line[i + 1] >wchar_t('9'))
		i++;

	while (Line[i] > wchar_t('9') || Line[i] < wchar_t('0') )
		i++;

	line = L"";
	while (true)
	{
		line+=Line[i];
		if (Line[i + 1] == wchar_t(','))
		{
			i = i + 2;
			break;
		}
		else
			i++;
	}
	Line.erase(Line.begin(), Line.begin() + i);
	y = Parsare::char_to_int(line);
	//Parsarea lui top left .y


	i = 0;
	line = L"";
	while (true)
	{
		line += Line[i];
		if (Line[i + 1] == wchar_t(','))
		{
			i = i + 2;
			break;
		}
		else
			i++;
	}
	Line.erase(Line.begin(), Line.begin() + i);
	x = Parsare::char_to_int(line);
	//Parsarea lui top left .x


	i = 0;
	line = L"";
	while (true)
	{
		line += Line[i];
		if (Line[i + 1] == wchar_t(','))
		{
			i = i + 2;
			break;
		}
		else
			i++;
	}
	Line.erase(Line.begin(), Line.begin() + i);
	width = Parsare::char_to_int(line);
	//Parsarea lui width


	i = 0;
	line = L"";
	while (true)
	{
		line += Line[i];
		if (i == Line.size() -1)
			break;
		if (Line[i + 1] == wchar_t(','))
		{
			i = i + 2;
			break;
		}
		else
			i++;
	}
	Line.erase(Line.begin(), Line.begin() + i);
	height = Parsare::char_to_int(line);
	//Parsarea lui height

	OBJ.Set_position(x, y, height, width);
	//Setarea valorilor
}

//return the integer writen in a wstring
int Parsare::char_to_int(wstring &line)
{
	//good
	auto n = line.size();
	int result = 0;
	int i;

	for (i = 0; i < n; i++)
	{
		result = result * 10;
		result = result + (wchar_t(line[i]) - wchar_t('0'));
	}

	return result;

	//Transform a string to integer
}
