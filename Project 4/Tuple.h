#include <string>
#include <vector>

using namespace std;

class Tuple : public vector<string> {
	public:
		void addAttributeValue(string);
		string const getTupleValueAt(unsigned int);
};