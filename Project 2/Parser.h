#pragma once

#include <vector>

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

using namespace std;

class Parser {
	public:
		int myIndex;
		
		Parser();

		void parse(vector<Token>&);
		void match(tokenType);

		void parseFactList(vector<Token>&);
		void parseRuleList(vector<Token>&);

		void parseQueryList(vector<Token>&);
		void parsePredicateList(vector<Token>&, Rule&);

		void parseParamList(vector<Token>&, Predicate&);
		void parseSchemeList(vector<Token>&);

		void advanceIndex();
		void fillmyToken(vector<Token>&);

		void print(ofstream &);
		void printSchemes(ofstream&);

		void printFacts(ofstream&);
		void printRules(ofstream&);

		void printQueries(ofstream&);
		void printDomain(ofstream&);
};