#include "Datalog.h"
#include "Scanner.h"

#include <fstream>

using namespace std;

class Parser
{
	private:
		Datalog dp;
		Rule r;
		Predicate pr;
		Parameter pm;
		Scanner scan;
		Token t;
		void parseSchemeList();
		void parseScheme();
		void parseFactList();
		void parseFact();
		void parseRuleList();
		void parseRule();
		void parseQueryList();
		void parseQuery();
		void parsePredicateList();
		void parsePredicate();
		void parseParameterList();
		void parseParameter();
		void match(TokenType);
		void error(Token);
		
	public:
		Parser(char*, char*);
		
		void parseDatalog();
		Datalog getDatalogProg() const { return dp; }
		Rule getR() const { return r; }
		Predicate getPr() const { return pr; }
		Parameter getPm() const { return pm; }
		string errorToString();
		string toString();
};