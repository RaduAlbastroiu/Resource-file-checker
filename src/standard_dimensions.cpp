#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "standard_dimensions.h"
#include "height_issue.h"
#include "width_issue.h"


//Standard dimension checker
void standard_dimensions::check_dimensions(Accumulator &Accumulate_Issues, const vector<widget> &Dialog_controllers)
{
	initialize_vect_of_widgets(Dialog_controllers);

	initializeDimension();
	int valid;
	for (const widget &controller : Dialog_controllers)
	{

		if (! white_list(controller))
		{
			
			valid = check_dimensions_special_case(controller);
			// if it is a special case

			// vertical size of the widget
			int current_size = controller.Get_bottom() - controller.Get_top();
			
			// if the recomanded vertical size is bigger than the current vertical size
			if (valid > current_size)
			{
				//increase the nr of issues for this type
				nrissues_standard_dimensions++;

				unique_ptr < Issue > pointer = make_unique < height_issue >(controller,valid);

				Accumulate_Issues.push_issue(move(pointer));
			}
			else
			{
				// if it is an ordinary case

				// if this type of controller exist in the map
				if (standard_dimension_map.find(controller.Get_type()) != standard_dimension_map.end())
				{

					// valid becomes the correct height or 0 if the controller has the correct height
					valid = is_Valid_Height(controller, standard_dimension_map[controller.Get_type()].height);

					// vertical size of the widget
					int current_size = controller.Get_bottom() - controller.Get_top();

					// if the recomanded vertical size is bigger than the current vertical size
					if (valid > current_size)
					{
						//increase the nr of issues for this type
						nrissues_standard_dimensions++;

						unique_ptr < Issue > pointer = make_unique < height_issue >(controller,valid);

						Accumulate_Issues.push_issue(move(pointer));
					}
				}

				/*
				if (!is_Valid_Width(controller))		// if width is not valid, make issue
				{
					//increase the nr of issues for this type
					nrissues_standard_dimensions++;

					unique_ptr <Issue> pointer = make_unique < width_issue >(controller);

					Accumulate_Issues.push_issue(move(pointer));
				}
				*/
			}
		}
	}
}

int standard_dimensions::check_dimensions_special_case(const widget & controller)
{
	int correct_height;
	
	// compute correct height for check/radio button 
	correct_height = Check_radio_buttons_dimensions(controller);
	
	if (correct_height)
		return correct_height;

	// compute correct height for type text
	correct_height = Check_text_dimensions(controller);
	
	if (correct_height)
		return correct_height;

	// compute correct height for bigger editext
	correct_height = Check_for_bigger_editext(controller);
	
	if (correct_height)
		return correct_height;

	// compute correct height for special case with checkbox and groupbox under it
	correct_height = Check_for_custom_check_box_before_groupbox(controller);
	
	if (correct_height)
		return correct_height;

	return 0;
}

int standard_dimensions::Check_radio_buttons_dimensions(const widget & controller)
{
	if (controller.Is_checkbox() ||
		controller.Is_radio_button())
	{
		if (is_Valid_Height(controller, standard_dimension_for_CHECKBOX))
		{
			// height of the current widget
			int height = controller.Get_bottom() - controller.Get_top();
			

			// if the height is bigger than standard and it's not a mupliple of standard_dimension_for_text
			if (((height) > standard_dimension_for_CHECKBOX &&
				(height) % standard_dimension_for_text))
			{

				// if the height is closer to the standard_dimension_for_checkbox 
				// than the first multiple of dimension_for_text biger than the standard
				if (height - standard_dimension_for_CHECKBOX < height % standard_dimension_for_text)
					return standard_dimension_for_CHECKBOX;


				// decide to wich multiple of standard_dimension_for_text should be resized
				else
				{
					if (controller.Has_name())
					{
						return height - (height % standard_dimension_for_text);
					}
					else
					{
						if (height % standard_dimension_for_text < standard_dimension_for_text/2)
							return height - (height % standard_dimension_for_text);
						else
							return height + (standard_dimension_for_text - (height % standard_dimension_for_text));
					}
				}
			}
			
			// if height is smaller than the standard will return the standard_dimension
			if(( height ) < standard_dimension_for_CHECKBOX)
				return standard_dimension_for_CHECKBOX;
		}
	}
	
	return 0;
}

int standard_dimensions::Check_text_dimensions(const widget & controller)
{

	// height of the current widget
	int height = controller.Get_bottom() - controller.Get_top();
	
	if (controller.isTextLabel())
	{
		
		// if height is not a multiple of standard_dimension_for_text
		if (height % standard_dimension_for_text)

			// decide to wich multiple of standard_dimension_for_text should be resized
			if (controller.Has_name())
			{
				return height - (height % standard_dimension_for_text);
			}
			else
			{
				if( height % standard_dimension_for_text < 4)
					return height - (height % standard_dimension_for_text);
				else
					return height + (standard_dimension_for_text - (height % standard_dimension_for_text));
			}
			
	}
	
	return 0;
}

int standard_dimensions::Check_for_bigger_editext(const widget & controller)
{

	// height of the current widget
	int height = controller.Get_bottom() - controller.Get_top();

	if ( controller.isEditText() )
	{
		// if the height should not be tested 
		if ( height >= standard_dimension_for_bigger_EDITEXT )
			return 0;
		
		// if the height is correct 
		if ( height == standard_dimension_for_EDITTEXT )
			return 0;

		return standard_dimension_for_EDITTEXT;
	}
	return 0;
}



bool standard_dimensions::Check_for_custom_check_box_before_groupbox(const widget & controller)
{
	// height of the current widget
	int height = controller.Get_bottom() - controller.Get_top();

	if (controller.Is_checkbox())
	{
		if (height > special_case_check_box_min && height < special_case_check_box_max)
		{
			for (auto &iter : Dialog_controllers)
			{
				if (iter.Is_groupbox())
				{
					if (controller.Get_bottom() <= iter.Get_top() &&
						iter.Get_top() - controller.Get_bottom() < special_case_check_box_verification_distance)
						return true;
				}
			}
		}
	}
	return false;
}


//it initialize dimensions for standard dimensions 
void standard_dimensions::initializeDimension()
{
	//For standard_deminsions validator
	standard_dimension_map[L"PUSHBUTTON"].height = standard_dimension_for_PUSHBUTTON;
	standard_dimension_map[L"PUSHBUTTON"].width = 50;

	standard_dimension_map[L"DEFPUSHBUTTON"].height = standard_dimension_for_DEFPUSHBUTTON;
	standard_dimension_map[L"DEFPUSHBUTTON"].width = 50;

}

void standard_dimensions::initialize_vect_of_widgets(const vector<widget>& controllers)
{
	for (auto &iter : controllers)
	
		Dialog_controllers.push_back(iter);
	
}

//if height is appropriate for the widget type
int standard_dimensions::is_Valid_Height(const widget &w, int height)
{

	if ((w.Get_bottom() - w.Get_top()) == height)
		return 0;

	return height;
}

// white list contains cases that are not tested
bool standard_dimensions::white_list(const widget & controller)
{

	// ignore [LRC]Text without text 
	if (controller.isTextLabel() && !controller.Has_name())
		return true;

	if (controller.Is_browse_button())
		return true;

	if (controller.isTextLabel() && controller.Get_name() == L"Static" && (controller.Get_bottom() - controller.Get_top()) > 15)
		return true;
	
	if (Check_for_custom_check_box_before_groupbox(controller))
		return true;

	return false;
}

