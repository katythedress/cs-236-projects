#include "Parser.h"
#include "Relation.h"

#include <algorithm>

using namespace std;

class Database {
	private:
		Parser p;
		vector<Predicate> schemes;
		vector<Predicate> facts;
		vector<Predicate> queries;
		map<string, Relation> rels;    
		ofstream out;                   

	public:
		Database(char*, char*);
		void buildRelations();
		void parseSchemes();
		void setRelationScheme(Relation&, unsigned int);
		void parseFacts();
		void setTupleAttributeValues(Tuple&, unsigned int);
		void evalQueries();
		void toString();
		void queryToString(unsigned int, unsigned int);
};