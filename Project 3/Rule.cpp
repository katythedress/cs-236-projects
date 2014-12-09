#include "Rule.h"

using namespace std;

void Rule::setHead(Predicate p)
{
	head = p;
}

void Rule::addPredicate(Predicate p)
{
	predList.push_back(p);
}

void Rule::cleanRule()
{
	predList.clear();
}

string Rule::toString()
{
	stringstream out;
	out << head.toString() << " :- ";
	
	for (unsigned i = 0; i < predList.size(); i++)
	{
		out << predList[i].toString();
		
		if (i < predList.size()-1)
		{
			out << ",";
		}
	}

	return out.str();
}