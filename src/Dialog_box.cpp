//===============
//Dialog_box cpp:
//===============

#include "stdafx.h"
#include "widget.h"
#include "Dialog_box.h"
#include "Parsare_Input.h"
#include "Message_output.h"

// copy constructor for a dialog
Dialog_box::Dialog_box(const Dialog_box &dialog):
	Dialog_elements(dialog.Dialog_elements), ID(dialog.ID), widht(dialog.widht),
	height(dialog.height), row(dialog.row), tested(dialog.tested)
{
	flagWS_THICKFRAME = dialog.flagWS_THICKFRAME;
	flagWS_CHILD = dialog.flagWS_CHILD;
	flagWS_SYSMENU = dialog.flagWS_SYSMENU;
	flagWS_CAPTION = dialog.flagWS_CAPTION;
	flagWS_POPUP = dialog.flagWS_POPUP;
	flagDS_MODALFRAME = dialog.flagDS_MODALFRAME;
}

Dialog_box::Dialog_box(Parsare &OBJ)
{

	this->ID = OBJ.find_dialog_IDnr(this->widht, this->height, this->row);

	tested = OBJ.Is_requested_dialog(ID);

	this->Change_height(height);
	this->Change_width(widht);
	this->Change_row(row);

	if (this -> ID.size() == 0)
		return;

	// parsare_input
	Dialog_elements = OBJ.Get_dialog(*this);
	setButtons(Dialog_elements);
}

void Dialog_box::setButtons(const vector<widget> &dialogElements) {

	auto it_found_OK = find_if(dialogElements.begin(), dialogElements.end(), 
		[](const widget &element){
			return element.Get_name() == L"OK" && (element.isPushButton() || element.isDefPushButton());
		});

	if (it_found_OK != dialogElements.end()) {
		setButtonOK();
	}

	auto it_found_Cancel = find_if(dialogElements.begin(), dialogElements.end(),
			[](const widget &element) {
				return element.Get_name() == L"OK" && (element.isPushButton() || element.isDefPushButton());
			});

	if (it_found_Cancel != dialogElements.end()) {
		setButtonCancel();
	}
}

void Dialog_box::setFlags(const wstring &Line) {

	//setting flags;

	flagWS_THICKFRAME   	= (Line.find(L"WS_THICKFRAME")	!= wstring::npos ? true : flagWS_THICKFRAME);
	flagWS_CHILD			= (Line.find(L"WS_CHILD")		!= wstring::npos ? true : flagWS_CHILD);
	flagWS_SYSMENU			= (Line.find(L"WS_SYSMENU")		!= wstring::npos ? true : flagWS_SYSMENU);
	flagWS_CAPTION			= (Line.find(L"WS_CAPTION")		!= wstring::npos ? true : flagWS_CAPTION);
	flagWS_POPUP			= (Line.find(L"WS_POPUP")		!= wstring::npos ? true : flagWS_POPUP);
	flagDS_MODALFRAME		= (Line.find(L"DS_MODALFRAME")	!= wstring::npos ? true : flagDS_MODALFRAME);
	flagWS_BORDER			= (Line.find(L"WS_BORDER")		!= wstring::npos ? true : flagWS_BORDER);
	flagWS_SCROLL			= (Line.find(L"WS_SCROLL")		!= wstring::npos ? true : flagWS_SCROLL);
}

bool Dialog_box::isFrame() {
	return flagWS_CHILD && !buttonOK && !buttonCancel;
}
bool Dialog_box::isModal() {
	return isFrame() ? false :
					   flagWS_SYSMENU || flagWS_CAPTION || flagWS_BORDER || flagWS_POPUP;
}

bool Dialog_box::containsWidget(const widget &elem) const {
	return widht >= elem.Get_right() && height >= elem.Get_bottom();
}