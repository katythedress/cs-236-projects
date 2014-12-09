#include "Relation.h"

#include <fstream>

using namespace std;

Relation::Relation(string n) : name(n)
{
	// Empty but necessary constructor
}

string print(vector<string> vec)
{
	stringstream out;

	for (unsigned int i = 0; i < vec.size(); i++)
	{
		out << "(" << vec.at(i) << ")" << " ";
	}

	return out.str();
}

void Relation::setName(string n)
{
	name = n;
} 

void Relation::setScheme(Scheme schm)
{
	s = schm;
}

void Relation::addSchemeAttribute(string attr)
{
	s.addAttribute(attr);
}

void Relation::addTuple(Tuple t)
{
	tups.insert(t);
}

Tuple Relation::getTupleAt(unsigned int i)
{
	return *next(tups.begin(), i);
}

void Relation::clearTuples()
{
	tups.clear();
}

void Relation::clear()
{
	name = "";
	s.clearAttributes();
	tups.clear();
}

void Relation::select(unsigned int pos, string val)
{
	set<Tuple> newTups;

	for (auto& t : tups)
	{
		if (t.at(pos) == val)
		{
			newTups.insert(t);
		}
	}

	tups = newTups;
	setName("select");
}

void Relation::select(unsigned int pos1, unsigned int pos2)
{
	set<Tuple> newTups;

	for (auto& t : tups)
	{
		if (t.at(pos1) == t.at(pos2))
		{
			newTups.insert(t);
		}
	}

	tups = newTups;
	setName("select");
}

void Relation::project(map<unsigned int, string>& variables)
{
	set<Tuple> newTups;
	Scheme newScheme;
	Tuple t;

	for (auto& v : variables)
	{
		newScheme.addAttribute(s.getAttributes().at(v.first));
	}

	for (auto& tup : tups)
	{
		for (auto& v : variables)
		{
			t.addAttributeValue(tup.at(v.first));
		}

		if(variables.size() > 0)
		{
			newTups.insert(t);
			t.clear();
		}
	}

	tups = newTups;
	s = newScheme;
	setName("project");
}

void Relation::rename(map<unsigned int, string>& variables)
{
	Scheme newScheme;

	for (auto& v : variables)
	{
		newScheme.addAttribute(v.second);
	}

	s = newScheme;
	setName("rename");
}

void Relation::toString(ofstream& out)
{
	out << name << endl;

	if (tups.size() == 0)
	{
		return;
	}

	for (unsigned int i = 0; i < tups.size(); i++)
	{
		out << " ";

		for (unsigned int j = 0; j < s.getAttributes().size(); j++)
		{
			out << " " << s.getAttributes().at(j) << "=" << getTupleAt(i).getTupleValueAt(j);
		}

		out << endl;
	}
}