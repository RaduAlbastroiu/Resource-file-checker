//=================================================
//Validation class and derived classes cpp defined:
//=================================================

#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "dialog_dimensions.h"
#include "partial_overlapping.h"
#include "horizontal_alignment.h"
#include "sorting.h"
#include "standard_dimensions.h"
#include "column_alignment.h"
#include "padding.h"
#include "DialogMargins.h"
#include "DlgFlags.h"

int Valid::nrissues_dialog_dim = 0;
int Valid::nrissues_partial_ol = 0;
int Valid::nrissues_rows = 0;
int Valid::nrissues_column_alignment = 0;
int Valid::nrissues_standard_dimensions = 0;
int Valid::nrissues_padding_vertically = 0;
int Valid::nrissues_padding_horizontally = 0;
int Valid::nrissues_padding_groupbox_top = 0;
int Valid::nrissues_padding_groupbox_bot = 0;
int Valid::nrissues_padding_groupbox_left = 0;
int Valid::nrissues_padding_groupbox_right = 0;
int Valid::nrissues_padding_typecontrol = 0;
int Valid::nrIssuesDlgFlags = 0;
int Valid::nrIssuesDialogMargins = 0;
int Valid::nrissues_sort = 0;

vector<wstring> Valid::requested_validators{};
bool Valid::customized_validation = false;

void Valid::Get_issues(Dialog_box Dialog, Accumulator &Accumulate_Issues)
{

	int i = 0;
	int	n = Dialog.Get_nr_elements();

	for (i = 0; i < n; i++)
		Dialog_controllers.push_back(Dialog.Get_element(i));

	//All the issues found below will be moved to Accumulator class

	//creating the tree
	this->create_tree();


	//Check for dialog dimensions issue
	if (should_be_run(L"-dd")) {
		dialog_dimensions dialog_dim;
		dialog_dim.check_dialog_dimensions(Dialog, Accumulate_Issues);
	}

	//Check for overlapping issues
	if (should_be_run(L"-ol")) {
		partial_overlapping overlapping;
		overlapping.check_partial_overlapping(Accumulate_Issues, Dialog_controllers);
	}

	//Check for row issues
	if (should_be_run(L"-ha")) {
		horizontal_alignment row;
		row.check_rows(Accumulate_Issues, Dialog_controllers);
	}

	//Check for column issues
	if (should_be_run(L"-ca")) {
		column_alignment column(Dialog_controllers);
		column.check_column_alignment(Accumulate_Issues);
	}

	//Check if the controller has the standard dimension
	if (should_be_run(L"-sd")) {
		standard_dimensions standard;
		standard.check_dimensions(Accumulate_Issues, Dialog_controllers);
	}

	//Check for any padding issues

	if (should_be_run(L"-pd")) {
		padding obj_padding(Dialog_controllers);
		obj_padding.check_padding(Dialog, Accumulate_Issues, Dialog_controllers);
	}

	if (should_be_run(L"-dm")) {
		DialogMargins validator(Dialog, Dialog_controllers);
		validator.validate(Accumulate_Issues);
	}

	if (should_be_run(L"-df")) {
		DlgFlags(Dialog).validate(Accumulate_Issues);
	}

	//Sort the list of controllers
	if (should_be_run(L"-zo")) {
		//CURRENTLY DISABLED
		sorting sort;
		sort.check_sorting(Accumulate_Issues, Dialog_controllers);
	}
}


//tree creation
void Valid::create_tree()
{
	auto n = Dialog_controllers.size();
	int i;
	int j;
	bool val;
	
	vector<widget*> pointeri;

	for (i = 0; i < n; i++)
		pointeri.push_back(&Dialog_controllers[i]);

	sort_tree(pointeri);

	for (i = 0; i < n; i++)
	{
		for (j = i+1; j < n; j++)
		{
			//total overlapping -> if i is the father of j 
			val = pointeri[i]->contains_mid_of(*pointeri[j]);
			if (val == true && pointeri[i]->Get_type() == L"GROUPBOX")
				pointeri[j]->Change_father(pointeri[i]);
		}
	}

	//changing the depth for the controllers with no father(their are childs of the dialog)
	for (i = 0; i < n; i++)
	{
		if (!pointeri[i]->Has_father())
		{
			pointeri[i]->Set_deep(1);
		}
	}


	//changing the depth for the other controllers relative to their father
	for (i = 0; i < n; i++)
	{
		if (pointeri[i]->Has_father())
		{
			int deep = pointeri[i]->Get_father().Get_deep();
			pointeri[i]->Set_deep(deep+1);
		}
	}
}


//sorting the container for tree creation
void Valid::sort_tree(vector<widget*> &pointeri) {
	
	sort(pointeri.begin(), pointeri.end(),
		[](const widget* a, const widget* b) {
		return a->Get_top() < b->Get_top() || ( a->Get_top() == b->Get_top() && a->Get_left() < b->Get_left() );
	});
}


//Radio-check button list create
void Valid::create_control_list(vector<widget>::iterator it, vector<widget> &Dialog_controllers)
{
	control control;

	if (it->Is_radio_button())
		control.radio_button = true;

	if (it->Is_checkbox())
		control.check_box = true;
		
	control.elements.push_back(&*it);
	it++;

	for (; it != Dialog_controllers.end(); it++)
	{
		if (it->Has_Ws_group() || it->Get_type() != L"CONTROL" || 
			((control.check_box && it->Is_radio_button()) || 
				control.radio_button && it->Is_checkbox()))
			break;
		
		control.elements.push_back(&*it);
	}

	if (control.elements.size() > 1)
	{
		for (auto i : control.elements)
		{
			int dist = i->Get_top() - (i - 1)->Get_bottom();
			
			if (i->Get_row() != control.elements[0]->Get_row() &&
				dist < distance_between_controlitems &&
				dist >= distance_min_berween_controlitems)
			{
				control.distance = i->Get_top() - (i - 1)->Get_bottom();
				break;
			}
		}

		if (control.distance != 0 && control.distance < 2 && control.distance > 5)
		{
			control.good = false;
			return;
		}

		for (auto i : control.elements)
		{
			int dist = i->Get_top() - (i - 1)->Get_bottom();

			if (i->Get_row() != control.elements[0]->Get_row() &&
				dist < distance_between_controlitems &&
				dist != control.distance)
			{
				control.good = false;
				break;
			}
		}

	}
	
	control_list.push_back(control);
}

void Valid::set_requested_validators(const vector<wstring> &validators)
{
	requested_validators = validators;
}

void Valid::set_customized_validation(const bool &validation)
{
	customized_validation = validation;
}

bool Valid::should_be_run(const wstring &validator)
{
	return customized_validation == false || (customized_validation == true && 
		   find(requested_validators.begin(), requested_validators.end(), validator) != requested_validators.end());
}