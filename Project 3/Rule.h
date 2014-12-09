#include "Predicate.h"

using namespace std;

class Rule {
	private:
		Predicate head;
		vector<Predicate> predList;
	public:
		void setHead(Predicate);
		void addPredicate(Predicate);
		void cleanRule();
		Predicate getHead() const { return head; }
		vector<Predicate> getPredList() const { return predList; }
		string toString();
};