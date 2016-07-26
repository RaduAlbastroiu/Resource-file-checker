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
		// main method
		padding(const vector<widget> &Dialog_controllers);
		void check_padding(Dialog_box &dialog, Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers);

	private:
		static int vertical_distances[10][10];
		static int horizontal_distances[10][10];

		//keeps track of whether a widget was checked
		vector<bool> state;
		//copy of the vector for the dialog controllers
		vector<widget> dialogElements;

		//returns the key of the element in the matrix of distances (keys are defined)
		int getKey(const widget &element);

		//returns true if an element at a specific position was already checked
		bool wasChecked(const vector<widget>::iterator &elemIt);
		bool wasChecked(const int &pos);

		//set an element as checked
		void setChecked(const vector<widget>::iterator &elemIt);
		void setChecked(const int &pos);

		//returns true if both controllers are possible elements of a list
		//(at least one of them is a radiobutton/checkbox)
		bool areListElements(const widget &first, const widget &second);
		bool areRelated(const widget &first, const widget &second);

		//gets the elements of an unchecked layer
		vector<widget> getNextLayerElements();

		//returns true if the first widget is above the second one
		bool isAbove(const widget &first, const widget &second);
		//returns true if the first widget is below the second one
		bool isBelow(const widget &first, const widget &second);
		//returns true if the first widget is to the left of the second one
		bool isToLeft(const widget &first, const widget &second);
		//returns true if the first widget is to the right of the second one
		bool isToRight(const widget &first, const widget &second);

		//returns true if two widgets overlap on Ox and not on Oy
		bool intersectOnOx(const widget &A, const widget &B);
		//returns true if two widgets overlap on Oy and not on Ox
		bool intersectOnOy(const widget &A, const widget &B);

		//returns the expected distance of 2 elements (takes their type keys as parameters)
		int getExpectedVerticalDistance(const int &key1, const int &key2);
		int getExpVertDistListElems(const widget &first, const widget &second);
		int getExpectedHorizontalDistance(const int &key1, const int &key2);

		//computes the vertical distance between two elements
		//(the first widget must be above the second one for a corrent answer)
		int computeVerticalDistance(const widget &first, const widget &second);
		//(the first widget must be to the left)
		int computeHorizontalDistance(const widget &first, const widget &second);

		//validate a pair of widgets vertically
		void validatePairVertically(const widget &first, const widget &second, Accumulator &issueAccumulator);

		//validate a pair of widgets vertically
		void validatePairHorizontally(const widget &first, const widget &second, Accumulator &issueAccumulator);

		//validates a layer both vertically and horizontally
		void validateLayer(const vector<widget> &layerElems, Accumulator &issueAccumulator);


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