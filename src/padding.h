#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"


//vertical distances between controllers
#define VERTICAL_DISTANCE_UNKNOWN -1
#define HORIZONTAL_DISTANCE_UNKNOWN -1

//defining the possible check states
#define CHECKED true
#define NOT_CHECKED false

//each controller type has key for the matrixes of distances
#define KEY_IGNORED_CONTROLLER 0
#define KEY_PUSHBUTTON 1
#define KEY_DEFPUSHBUTTON 2
#define KEY_CHECKBOX 3
#define KEY_RADIOBUTTON 4
#define KEY_TEXTLABEL 5
#define KEY_EDITTEXT 6
#define KEY_GROUPBOX 7
#define KEY_LISTBOX 8
#define KEY_DROPDOWNLIST 9

//distances for the start and end of a list by controllers
#define NEW_LIST_TEXTLABEL 0
#define NEW_LIST_CHECK_RADIO 2
#define END_LIST 4

class padding : public Valid
{
public:
	padding() = default;
	padding(const vector<widget> &Dialog_controllers);

	// main method
	void check_padding(Dialog_box &dialog, Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers);

protected:
	static int vertical_distances[10][10];
	static int horizontal_distances[10][10];


	//copy of the vector for the dialog controllers
	vector<widget> dialogElements;

	//returns the key of the element in the matrix of distances (keys are defined)
	int getKey(const widget &element);

	//returns true if both controllers are possible elements of a list
	//(at least one of them is a radiobutton/checkbox)
	bool areListElements(const widget &first, const widget &second);
	bool areRelated(const widget &first, const widget &second) { return first.Get_left() == second.Get_left(); }


	//returns true if the first widget is above the second one
	bool isAbove(const widget &first, const widget &second) { return first.Get_top() < second.Get_top(); }
	//returns true if the first widget is below the second one
	bool isBelow(const widget &first, const widget &second) { return first.Get_bottom() > second.Get_bottom(); }
	//returns true if the first widget is to the left of the second one
	bool isToLeft(const widget &first, const widget &second) { return first.Get_left() < second.Get_left(); }
	//returns true if the first widget is to the right of the second one
	bool isToRight(const widget &first, const widget &second) { return first.Get_right() > second.Get_right(); }

	//returns true if two widgets overlap on Ox and not on Oy
	bool intersectOnOx(const widget &A, const widget &B);
	//returns true if two widgets overlap on Oy and not on Ox
	bool intersectOnOy(const widget &A, const widget &B);

	//returns the expected distance of 2 elements (takes their type keys as parameters)
	int getExpectedVerticalDistance(const int &key1, const int &key2) { return vertical_distances[key1][key2]; }
	int getExpVertDistListElems(const widget &first, const widget &second);
	int getExpectedHorizontalDistance(const int &key1, const int &key2) { return horizontal_distances[key1][key2]; }

	//computes the vertical distance between two elements
	//(the first widget must be above the second one for a corrent answer)
	int computeVerticalDistance(const widget &first, const widget &second) { return second.Get_top() - first.Get_bottom(); }
	//(the first widget must be to the left)
	int computeHorizontalDistance(const widget &first, const widget &second) { return second.Get_left() - first.Get_right(); }


	//groupbox validation
	//distance validation between the groupbox and the 
	//uppermost, lowermost, leftmost, rightmost controllers
	//for each not respected distance, an issue is pushed
	void valid_check_top_groupbox(const widget& father, Accumulator &Accumulate_Issues);
	void valid_check_bot_groupbox(const widget& father, Accumulator &Accumulate_Issues);
	void valid_check_left_groupbox(const widget& father, Accumulator &Accumulate_Issues);
	void valid_check_right_groupbox(const widget& father, Accumulator &Accumulate_Issues);

	//checkbutton & radiobutton validation
	//if the distance in between two radio or check buttons from the same list is the same

};