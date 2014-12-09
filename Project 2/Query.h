#pragma once

#include "Predicate.h"

using namespace std;

class Query {
	public:
		Predicate myPred;

		Query(Predicate);
};