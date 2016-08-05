#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"
#include "standard_dimensions.h"
#include "height_issue.h"
#include "width_issue.h"
#include "padding.h"
#include "padding_for_min_distance.h"
#include "padding_issue_vertically.h"
#include "padding_issue_horizontally.h"
#include "padding_issue_top.h"
#include "padding_issue_bot.h"
#include "padding_issue_right.h"
#include "padding_issue_left.h"
#include "padding_issue_type_control.h"


// constructor 
padding_for_min_distance::padding_for_min_distance(vector<widget> &dialog_elements)
	: dialogElements(dialog_elements)
{
	state.resize(dialogElements.size());
}

// main method for checking min padding distance
void padding_for_min_distance::check_padding_for_min_distance(Accumulator &Accumulate_Issues)
{
	vector<widget> currentLayerElements = getNextLayerElements();

	while (!currentLayerElements.empty()) {
		validateLayer(currentLayerElements, Accumulate_Issues);
		currentLayerElements = getNextLayerElements();
	}
}

vector<widget> padding_for_min_distance::getNextLayerElements()
{

	//find an element which has not been checked yet
	auto itLayerElement = find(state.begin(), state.end(), NOT_CHECKED);

	//returns an empty widget vector if there are no more elements to check
	if (itLayerElement == state.end()) {
		return vector<widget>();
	}

	//the position of the element in the vector
	int elemPos = itLayerElement - state.begin();

	//copy the current element's father
	widget *currentLayerFather = dialogElements[elemPos].Get_father_pointer();

	//copy the elements of the current layer (their father is currentLayerFather)
	vector<widget> layerElements;
	for (auto it = dialogElements.begin(), end = dialogElements.end(); it != end; it++) {
		if (it->Get_father_pointer() == currentLayerFather) {

			if (!it->Is_browse_button() && !it->Is_transparent()) {
				layerElements.push_back(*it);
			}

			setChecked(it);
		}
	}

	//return the current layer elements
	return layerElements;
}


void padding_for_min_distance::validateLayer(const vector<widget> &layerElems, Accumulator &issueAccumulator)
{

	for (int it1 = 0, size = layerElems.size(); it1 < size; it1++) {
		for (int it2 = it1 + 1; it2 < size; it2++) {

			//validate each pair of the current layer vertically and horizontally
			validatePairVertically(layerElems[it1], layerElems[it2], issueAccumulator);
			validatePairHorizontally(layerElems[it1], layerElems[it2], issueAccumulator);
		}
	}
}

void padding_for_min_distance::validatePairHorizontally(const widget &first, const widget &second, Accumulator &issueAccumulator)
{

	//skip this pair if widgets are not one next to the other
	if (!intersectOnOy(first, second)) {
		return;
	}

	//keep track of which element is above and which is below
	widget elemToLeft = isToLeft(first, second) ? first : second;
	widget elemToRight = isToRight(first, second) ? first : second;

	//find their keys
	int keyElemToLeft = getKey(elemToLeft);
	int keyElemToRight = getKey(elemToRight);

	//get the expected and actual distance of the two elements
	int expectedDistance = getExpectedHorizontalDistance(keyElemToLeft, keyElemToRight);
	int actualDistance = computeHorizontalDistance(elemToLeft, elemToRight);

	//skip pairs for which the expected distance is unknown
	if (expectedDistance == HORIZONTAL_DISTANCE_UNKNOWN) {
		return;
	}

	if (expectedDistance > actualDistance) {

		nrissues_padding_horizontally++;

		//NOTE : SEND THEIR DISTANCEBETWEEN AS PARAMETER
		int distanceForFix = expectedDistance - actualDistance;

		unique_ptr<Issue> pointer = make_unique< padding_issue_horizontally >(elemToLeft, elemToRight, distanceForFix);
		issueAccumulator.push_issue(move(pointer));
	}
}

void padding_for_min_distance::validatePairVertically(const widget &first, const widget &second, Accumulator &issueAccumulator) {

	//skip this pair if widgets are not one above the other
	if (!intersectOnOx(first, second)) {
		return;
	}

	//keep track of which element is above and which is below
	widget elemAbove = isAbove(first, second) ? first : second;
	widget elemBelow = isBelow(first, second) ? first : second;

	//find their keys
	int keyElemAbove = getKey(elemAbove);
	int keyElemBelow = getKey(elemBelow);

	//get the expected and actual distance of the two elements
	int expectedDistance;
	if (areListElements(elemAbove, elemBelow) && !areRelated(elemAbove, elemBelow)) {
		expectedDistance = getExpVertDistListElems(elemAbove, elemBelow);
	}
	else {
		expectedDistance = getExpectedVerticalDistance(keyElemAbove, keyElemBelow);
	}
	int actualDistance = computeVerticalDistance(elemAbove, elemBelow);

	//skip pairs for which the expected distance is unknown
	if (expectedDistance == VERTICAL_DISTANCE_UNKNOWN) {
		return;
	}

	// Skip Textlabesl without text
	if ((first.isTextLabel() && !first.Has_name()) || (second.isTextLabel() && !second.Has_name()))
		return;

	// Skip Textlabesl without text
	if ( first.Is_transparent() || second.Is_transparent())
		return;

	if (expectedDistance > actualDistance) {

		nrissues_padding_vertically++;

		//NOTE : SEND THEIR DISTANCEBETWEEN AS PARAMETER
		int distanceForFix = expectedDistance - actualDistance;

		unique_ptr<Issue> pointer = make_unique<padding_issue_vertically>(elemAbove, elemBelow, distanceForFix);
		issueAccumulator.push_issue(move(pointer));
	}
}
