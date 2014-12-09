#pragma once

#include "Predicate.h"

using namespace std;

class Fact {
	public:
		Predicate myPred;

		Fact(Predicate);
};