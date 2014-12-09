#include "Scheme.h"
#include "Tuple.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Relation
{
	private:
		string name;
		Scheme s;
		set<Tuple> tups;

	public:
		Relation() {};
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
		void project(vector<unsigned int>&);
		void rename(vector<string>&);
		void join(Relation&);
		void makeScheme(vector<string>&, vector<string>&);
		bool canJoin(vector<string>&, Tuple&, vector<string>&, Tuple&);
		Tuple makeTuple(vector<string>&, Tuple&, vector<string>&, Tuple&);
		void relationUnion(Relation&, ofstream&);
		void toString(ofstream&);
};