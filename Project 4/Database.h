#include "Parser.h"
#include "Relation.h"

#include <algorithm>

using namespace std;

class Database {
	private:
		Parser p;
		vector<Predicate> schemes;
		vector<Predicate> facts;
		vector<Rule> rules;
		vector<Predicate> queries;
		map<string, Relation> rels;    
		ofstream out;
		unsigned int size;

	public:
		Database(char*, char*);
		unsigned int getSize();
		void buildRelations();
		void parseSchemes();
		void setRelationScheme(Relation&, unsigned int);
		void parseFacts();
		void setTupleAttributeValues(Tuple&, unsigned int);
		void evaluateRules();
		void forEachParameter(vector<Parameter>&, Relation&, unsigned int&, map<string, unsigned int>&, map<unsigned int, string>&);
		void evaluateQueries();
		void toString();
		void queryToString(unsigned int, unsigned int);
};