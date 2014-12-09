#include "Tuple.h"

using namespace std;

void Tuple::addAttributeValue(string val)
{
	push_back(val);
}

string const Tuple::getTupleValueAt(unsigned int i)
{
	return at(i);
}