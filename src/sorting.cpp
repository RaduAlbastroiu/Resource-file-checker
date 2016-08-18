#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "sorting.h"
#include "sorting_issue.h"


//sorting issue class checker
void sorting::check_sorting(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers)
{
	auto unorderedBuckets = getGroupedWidgets(Dialog_controllers);

	// create a Z-ordered copy of the elements
	auto sortedBuckets = getOrderedBuckets(unorderedBuckets);

	// checking if there is the same order
	bool isSameOrder = equal(unorderedBuckets.begin(), unorderedBuckets.end(), sortedBuckets.begin(), sortedBuckets.end(),
		[](const bucket& first, const bucket& second) {
			return first.front() == second.front();
	});

	// if there is not the same order then report an issue with the suggested order
	if (!isSameOrder) 
	{
		nrissues_sort++;

		auto ptr = make_unique<sorting_issue>(getElementsFromBuckets(sortedBuckets));
		Accumulate_Issues.push_issue(move(ptr));
	}
}

vector<sorting::bucket> sorting::getGroupedWidgets(const vector<widget>& elements) {

	vector < bucket > groupedWidgets;

	using elemIter = vector<widget>::const_iterator;

	elemIter beginCopyRange;
	elemIter endCopyRange;

	// create widget vectors such that the elements in a vector are part of a group
	// (a group of controllers is a list of control declarations, the first one having the flag WS_GROUP)
	for (elemIter iter = elements.begin(); iter != elements.end();) 
	{
		// find the copy range
		beginCopyRange = iter;
		endCopyRange   = iter + 1;

		// the range that needs to be copied for a WS_GROUP control is formed by all the controls declared below it including it
		if (iter->isControl() && iter->Has_Ws_group()) 
		{
			endCopyRange = find_if(iter + 1, elements.end(),
				[&](const auto& wid) {
					
					auto father = iter->Get_father_pointer();

					// TODO: check if the father of wid is a transparent groupbox
					return !(wid.Is_radio_button() || wid.Is_checkbox()) || 
						   ((wid.Is_radio_button() || wid.Is_checkbox()) && (wid.Has_Ws_group() || wid.Get_left() != iter->Get_left() || wid.Get_father_pointer() != iter->Get_father_pointer()));
				});
		}

		// create the bucket and put the widget(s) in it
		groupedWidgets.emplace_back();
		copy(beginCopyRange, endCopyRange, back_inserter(groupedWidgets.back()));

		iter = endCopyRange;
	}

	return groupedWidgets;
}

vector<vector<widget>> sorting::getOrderedBuckets(vector<bucket> unorderedBuckets) {
	sort(unorderedBuckets.begin(), unorderedBuckets.end(), comp);
	
	return unorderedBuckets;
}

vector<widget> sorting::getElementsFromBuckets(const vector<bucket>& sortedBuckets) {
	
	vector<widget> orderedElements;

	for (const auto& currentBucket : sortedBuckets) {
		copy(currentBucket.begin(), currentBucket.end(), back_inserter(orderedElements));
	}

	return orderedElements;
}

bool sorting::comp(const bucket& firstBucket, const bucket& secondBucket)
{
	// Buckets are compared by their front element
	auto& first = firstBucket.front();
	auto& second = secondBucket.front();

	int middle1 = (first.Get_top()  + first.Get_bottom())  / 2;
	int middle2 = (second.Get_top() + second.Get_bottom()) / 2;

	// If an object contains another then that object should be put before the other one 
	if (second.contains(first))
		return false;

	if (first.contains(second))
		return true;

	// Order them from left to right if the middle of an object intersects the middle of the other one
	if ((first.Get_top()  <= middle2 && middle2 <= first.Get_bottom()) || 
		(second.Get_top() <= middle1 && middle1 <= second.Get_bottom()))
	{
		return first.Get_left() < second.Get_left();
	}

	// Otherwise order them by top
	return first.Get_top() < second.Get_top();
}
