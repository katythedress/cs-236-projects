#include "Scheme.h"
#include "Tuple.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Relation {
	private:
		string name;
		Scheme s;
		set<Tuple> tups;

	public:
		Relation(){};
		Relation(string);
		void setName(string);
		void setScheme(Scheme);
		void addSchemeAttribute(string);
		void addTuple(Tuple);
		Tuple getTupleAt(unsigned int);
		string getName() const { return name; }
		Scheme getScheme() const { return s; }
		set<Tuple> getTuples() const { return tups; }
		void clearTuples();
		void clear();
		void select(unsigned int, string);
		void select(unsigned int, unsigned int);
		void project(map<unsigned int, string>&);
		void rename(map<unsigned int, string>&);
		void toString(ofstream&);
};