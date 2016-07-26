#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include <map>


class column_alignment : public Valid
{
	private:
		//the vector of elements which are checked
		vector<widget> elements;

		//checkedElements[x] is true if the i-th item of elements was already checked
		vector<bool> checkedElements;

		/*
		  Have a map where the key is the column and each element of the map is a vector of 
		  widgets left aligned to that column (key).
		  For each layer a map will be created.
		 */
		map<int, vector<widget>> createMap(const vector<widget> &controllers);

		//Gets the position of an object of the elements vector to which an iterator points
		int getPositionOfIterator(const vector<widget>::iterator &it);

		//returns true if the element to which iterator it points was already checked
		bool wasChecked(const vector<widget>::iterator &it);
		bool wasChecked(const int &position);

		//chooses the widgets in the elements vector which have the same father
		vector<widget> chooseWidgetsSameFather(widget *current_father);

		//sets an element as checked
		void setAsChecked(const vector<widget>::iterator &it);

		//checks the chosen elements and adds them to the issues container
		void check_current_elements(const vector<widget> &current_elements, Accumulator &Accumulate_Issues);

		//adds the issues of the unaligned elements to the issues container
		void append_issues(const int &column, const vector<widget> &unaligned_elements, Accumulator &Accumulate_Issues);

	public:

		

		//makes a copy of the controllers, sets the checked vector equal to the size of controolers and 
		//initializes all of its elements with 0
		column_alignment(const vector <widget> &controllers);

		//Validation of the controllers based on left column alignment
		void check_column_alignment(Accumulator &Accumulate_Issues);
};