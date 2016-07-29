#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "column_alignment.h"
#include "column_alignment_issue.h"

column_alignment::column_alignment(const vector<widget> &controllers)
{
	elements = controllers;
	checkedElements.resize(elements.size());
}

map<int, vector<widget>> column_alignment::createMap(const vector<widget> &controllers) {
	map<int, vector<widget>> leftColumns;

	/*
	 Put each widget in a bucket corresponding to its left column
	*/
	for (const auto &controller : controllers) {

		//Browse buttons, pushbuttons, defpushbuttons and groupboxes are ignored.
		if (!controller.Is_browse_button() && !controller.isPushButton() && !controller.isDefPushButton() && !controller.Is_transparent()) {
			int key = controller.Get_left();
			leftColumns[key].push_back(controller);
		}
	}

	/*
	 Iterate through the elements of the map
	*/
	for (auto &Column : leftColumns) {

		//Sort each of the vectors in the map increasingly based on the top of the contained controllers.
		sort(Column.second.begin(), Column.second.end(),
			[](const widget &w1, const widget &w2) {
			return w1.Get_top() < w2.Get_top();
		});
	}

	return leftColumns;
}

void column_alignment::check_column_alignment(Accumulator &Accumulate_Issues) {

	vector<widget> current_elements;

	//find unmarked elements
	for (auto it = elements.begin(), end = elements.end(); it != end; it++) {
		
		//position of the current element
		int position = getPositionOfIterator(it);

		//skip this element if it was already checked
		if (wasChecked(position))
			continue;
		
		//get the father of the current element
		widget *current_father = it->Get_father_pointer();

		//gather the widgets with the same father
		current_elements = chooseWidgetsSameFather(current_father);

		//check and append the issues of the elements
		check_current_elements(current_elements, Accumulate_Issues);
	}
}

int column_alignment::getPositionOfIterator(const vector<widget>::iterator &it) {
	return (int)(it - elements.begin());
}

bool column_alignment::wasChecked(const vector<widget>::iterator &it) {
	return checkedElements[it - elements.begin()];
}

bool column_alignment::wasChecked(const int &position) {
	return checkedElements[position];
}

vector<widget> column_alignment::chooseWidgetsSameFather(widget *current_father) {
	vector<widget> chosenWidgets;

	//Choose widgets with the current father and mark them as checked
	for (auto it = elements.begin(), end = elements.end(); it != end; it++) {
		if (it->Get_father_pointer() == current_father) {

			//add the element to the chosen elements only if it is not a pushbutton, defpushbutton or browsebutton
			if (!it->isPushButton() && !it->isDefPushButton() && !it->Is_browse_button()) {
				chosenWidgets.push_back(*it);
			}
			
			//mark it as checked
			setAsChecked(it);
		}
	}
	
	//return the chosen widgets
	return chosenWidgets;
}

void column_alignment::setAsChecked(const vector<widget>::iterator &it) {
	int position = getPositionOfIterator(it);
	checkedElements[position] = true;
}

void column_alignment::check_current_elements(const vector<widget> &current_elements, Accumulator & Accumulate_Issues) {

	//alignedElements[C] will contain all the widgets left aligned at column C 
	map<int, vector<widget>> alignedElements = createMap(current_elements);

	//There is no need for validation if there are no more than 2 elements
	if (alignedElements.size() < 2)
		return;

	//start with iterators to the first two elements of the map
	auto it_prev = alignedElements.begin();
	auto it_current = alignedElements.begin();
	it_current++;

	//iterate through the map (for each 2 columns to which elements are left aligned)
	for (auto end = alignedElements.end(); it_current != end; it_current++) {

		//get the distance between the columns

		int prev_column =  it_prev->first;
		int current_column = it_current->first;
		int distance = current_column - prev_column;

		//number of elements aligned to prev and current columns
		int nr_aligned_prev = it_prev->second.size();
		int nr_aligned_current = it_current->second.size();

		//the value of each column
		int prev_col = it_prev->first;
		int current_col = it_current->first;

		//distance between columns not respected, might be a mistake
		if (distance < column_space) {
			//number of controllers left aligned to a column is different from the other, might be a mistake
			if (nr_aligned_current < max_unaligned_controlers && nr_aligned_current < nr_aligned_prev) {
				append_issues(prev_col, it_current->second, Accumulate_Issues);
			}
			else if (nr_aligned_prev < max_unaligned_controlers && nr_aligned_current > nr_aligned_prev) {
				append_issues(current_col, it_prev->second, Accumulate_Issues);
			}
			//special case: to each column only one controller is left aligned, then both controllers should be aligned
			//to the leftmost column
			else if (nr_aligned_prev == 1 && nr_aligned_current == 1) {
				append_issues(prev_col, it_current->second, Accumulate_Issues);
			}
		}
		
		//the current and the following column will be tested next
		//so the current column becomes the previous one 
		it_prev = it_current;
	}
}

void column_alignment::append_issues(const int &column, const vector<widget> &unaligned_elements, Accumulator &Accumulate_Issues) {
	for (const auto &element : unaligned_elements) {
		//increment the counter for this type of issues
		nrissues_column_alignment++;

		//add the issue to the container
		unique_ptr <Issue> pointer = make_unique <column_alignment_issue>(element, column);
		Accumulate_Issues.push_issue(move(pointer));
	}
}