#include "Parameter.h"

#include <vector>

using namespace std;

class Predicate {
	private:
		string ident;
		vector<Parameter> paramList;
	public:
		void setIdentity(string);
		void addParameter(Parameter);
		void cleanPredicate();
		string getIdentity() const { return ident; }
		vector<Parameter> getParameterList() const { return paramList; }
		string toString();
};