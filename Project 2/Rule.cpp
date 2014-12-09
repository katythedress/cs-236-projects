#include "Rule.h"

using namespace std;

Rule::Rule(Predicate p)
{
	myPred = p;
}

void Rule::addPredicate(Predicate p)
{
	predList.push_back(p);
}