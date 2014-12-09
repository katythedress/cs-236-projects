#include "Graph.h"
#include "Parser.h"
#include "Relation.h"

#include <algorithm>
#include <cstdlib>

using namespace std;

class Database
{
	private:
		Parser p;
		Graph dependancyGraph;
		vector<Predicate> schemes;
		vector<Predicate> facts;
		vector<Rule> rules;
		vector<Rule> rulesToEval;
		vector<Predicate> queries;
		map<string, Relation> rels;    
		ofstream out;
		int size;

	public:
		Database(char*, char*);
		
		int getSize();
		void buildRelations();
		void parseSchemes();
		void setRelationScheme(Relation&, unsigned int);
		void parseFacts();
		void setTupleAttributeValues(Tuple&, unsigned int);
		void buildDependancyGraph();
		void buildDependancyGraphStuff();
		void evaluateRules();
		void getRulesToEvaluate();
		void forEachParameter(vector<Parameter>&, Relation&, unsigned int&, map<string, unsigned int>&, map<unsigned int, string>&);
		void evaluateQueries();
		void evalQuery(Predicate);
		void toString();
		void queryToString(Predicate, unsigned int);
};