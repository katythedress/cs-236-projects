#include "Halp.h"

#include <string>

using namespace std;

int Halp::stringToInt(string s)
{
	int i = atoi(s.c_str());

	return i;
}

string Halp::intToString(int i)
{
	ostringstream strm;
	strm << i;

	return strm.str();
}