#pragma once
#include "stdafx.h"
#include "Dialog_box.h"
#include "widget.h"
#include "Issue.h"
#include "Valid.h"
#include "Accumulator.h"

class sorting : public Valid
{
	private:
		using bucket = vector<widget>;

		// builds a vector of buckets where each bucket is formed by the elements in the same group
		// if an element is not in a group then its bucket will contain only that element
		vector< bucket > getGroupedWidgets(const vector<widget>& elements);

		// transforms a vector of buckets into a vector of widgets
		vector<widget> getElementsFromBuckets(const vector<bucket>& sortedBuckets);

		// sorting criteria
		static bool comp(const bucket &firstBucket, const bucket &secondBucket);

	public:
		bool valid = true;

		void check_sorting(Accumulator &Accumulate_Issues, vector<widget> &Dialog_controllers);
		
		

};