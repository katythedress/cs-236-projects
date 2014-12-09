#pragma once

#include <vector>

#include "Predicate.h"

using namespace std;

class Rule {
	public:
		Predicate myPred;
		vector<Predicate> predList;

		Rule(Predicate);

		void addPredicate(Predicate); // Push parameter onto vector
};