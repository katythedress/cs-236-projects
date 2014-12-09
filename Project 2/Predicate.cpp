#include "Predicate.h"

using namespace std;

Predicate::Predicate()
{
	// Overloaded garbage
}

Predicate::Predicate(string data)
{
	info = data;
}

void Predicate::addParameter(Parameter p)
{
	paramList.push_back(p);
}

void Predicate::setInfo(string s)
{
	info = s;
}

string Predicate::toString()
{
	ostringstream sb;
	sb << "  " << info << "(";

	return sb.str();
}