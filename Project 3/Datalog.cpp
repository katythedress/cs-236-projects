#include "Datalog.h"

using namespace std;

void Datalog::addScheme(Predicate s)
{
	schemes.push_back(s);
}

void Datalog::addFact(Predicate f)
{
	facts.push_back(f);
}

void Datalog::addQuery(Predicate q)
{
	queries.push_back(q);
}

void Datalog::addRule(Rule r) {
	rules.push_back(r);
}

void Datalog::addValue(string str)
{
	values.insert(str);
}

string Datalog::toString()
{
	stringstream out;
	out << "Schemes(" << schemes.size() << "):\n";

	for (unsigned i = 0; i < schemes.size(); i++)
	{
		out << "  " << schemes[i].toString() << endl;
	}

	out << "Facts(" << facts.size() << "):\n";
	
	for (unsigned i = 0; i < facts.size(); i++)
	{
		out << "  " << facts[i].toString() << endl;
	}

	out << "Rules(" << rules.size() << "):\n";

	for (unsigned i = 0; i < rules.size(); i++)
	{
		out << "  " << rules[i].toString() << endl;
	}

	out << "Queries(" << queries.size() << "):\n";

	for (unsigned i = 0; i < queries.size(); i++)
	{
		out << "  " << queries[i].toString() << endl;
	}

	out << "Domain(" << values.size() << "):";
	set<string>::iterator it;

	for (it = values.begin(); it != values.end(); it++)
	{
		string s = *it;
		out << endl << "  \'" << s << "\'";
	}
	
	return out.str();
}