#pragma once

#include "Parameter.h"

#include <sstream>
#include <vector>

using namespace std;

class Predicate {
	public:
		Predicate();
		Predicate(string); // Overloading

		void addParameter(Parameter); // Push parameter onto vector
		void setInfo(string);

		string toString();

		string info;
		vector<Parameter> paramList;
};