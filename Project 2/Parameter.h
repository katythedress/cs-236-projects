#pragma once

#include <iostream>
#include <sstream>

#include "Token.h"

using namespace std;

class Parameter {
	public:
		string info;
		tokenType type; // ID or string?

		Parameter(string, tokenType);

		string toString();
};