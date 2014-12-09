#include "Rule.h"

#include <set>

using namespace std;

class Datalog {
	private:
		vector<Predicate> schemes;
		vector<Predicate> facts;
		vector<Predicate> queries;
		vector<Rule> rules;
		set<string> values;

	public:
		Datalog(){};
		void addScheme(Predicate);
		void addFact(Predicate);
		void addQuery(Predicate);
		void addRule(Rule);
		void addValue(string);
		vector<Predicate> getSchemes() const { return schemes; }
		vector<Predicate> getFacts() const { return facts; }
		vector<Predicate> getQueries() const { return queries; }
		vector<Rule> getRules() const { return rules; }
		string toString();
};