#include "Relation.h"

#include <fstream>

using namespace std;

Relation::Relation(string n) : name(n) {}

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

void Relation::project(vector<unsigned int>& variablePos)
{
	set<Tuple> newTups;
	Scheme newScheme;
	Tuple t;

	for (auto& v : variablePos)
	{
		newScheme.addAttribute(s.getAttributes().at(v));
	}

	for (auto& tup : tups)
	{
		for (auto& v : variablePos)
		{
			t.addAttributeValue(tup.at(v));
		}

		if (variablePos.size() > 0)
		{
			newTups.insert(t);
			t.clear();
		}
	}

	tups = newTups;
	s = newScheme;
	setName("project");
}

void Relation::rename(vector<string>& variableName)
{
	Scheme newScheme;

	for (auto& v : variableName)
	{
		newScheme.addAttribute(v);
	}

	s = newScheme;
	setName("rename");
}

void Relation::join(Relation& r)
{
	vector<string> s1 = getScheme().getAttributes();
	vector<string> s2 = r.getScheme().getAttributes();
	set<Tuple> tups1 = getTuples();
	set<Tuple> tups2 = r.getTuples();
	clearTuples();
	makeScheme(s1, s2);

	for (Tuple t1 : tups1)
	{
		for (Tuple t2 : tups2)
		{
			if (canJoin(s1, t1, s2, t2))
			{
				addTuple(makeTuple(s1, t1, s2, t2));
			}
		}
	}  
}

void Relation::makeScheme(vector<string>& s1, vector<string>& s2)
{
	for (auto& name : s2)
	{
		if (!count(s1.begin(), s1.end(), name))
		{
			s.addAttribute(name);
		}
	}
}

bool Relation::canJoin(vector<string>& s1, Tuple& t1, vector<string>& s2, Tuple& t2)
{
	for (unsigned int i = 0; i < t1.size(); i++)
	{
		for (unsigned int j = 0; j < t2.size(); j++)
		{
			if (s1.at(i) == s2.at(j) && t1.at(i) != t2.at(j))
			{
				return false;
			}
		}
	}

	return true;
}

Tuple Relation::makeTuple(vector<string>& s1, Tuple& t1, vector<string>& s2, Tuple& t2)
{
	Tuple t3 = t1;

	for (unsigned int i = 0; i < t2.size(); i++)
	{
		if (!count(s1.begin(), s1.end(), s2.at(i)))
		{
			t3.addAttributeValue(t2.at(i));
		}
	}

	return t3;
}

void Relation::relationUnion(Relation& r, ofstream& out)
{
	set<Tuple> tups1 = getTuples();
	set<Tuple> tups2 = r.getTuples();

	for (Tuple t2 : tups2)
	{
		if (!tups1.count(t2))
		{
			addTuple(t2);
			out << " ";

			for (unsigned int j = 0; j < s.getAttributes().size(); j++)
			{
				out << " " << s.getAttributes().at(j) << "=" << t2.getTupleValueAt(j);
			}

			out << endl;
		}
	}
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