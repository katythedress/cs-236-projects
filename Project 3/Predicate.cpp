#include "Predicate.h"

using namespace std;

void Predicate::setIdentity(string s)
{
	ident = s;
}

void Predicate::addParameter(Parameter p)
{
	paramList.push_back(p);
}

void Predicate::cleanPredicate()
{
	paramList.clear();
}

string Predicate::toString()
{
	stringstream out;
	out << ident << "(";
	
	for (unsigned i = 0; i < paramList.size(); i++)
	{
		out << paramList[i].getValue();

		if(i < paramList.size()-1)
		{
			out << ",";
		}
	}
	
	out << ")";
	
	return out.str();
}