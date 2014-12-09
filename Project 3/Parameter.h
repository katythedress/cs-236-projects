#include <sstream>
#include <string>

using namespace std;

class Parameter {
	private:
		string value;

	public:
		Parameter(){}
		void setValue(string);
		string getValue() const { return value; }
		string toString();
};