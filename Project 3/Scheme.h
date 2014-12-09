#include <string>
#include <vector>

using namespace std;

class Scheme {
	private:
		vector<string> attributeNames;
	public:
		Scheme(){};
		void addAttribute(string);
		void setAttributeAt(unsigned int, string);
		vector<string> getAttributes() const { return attributeNames; }
		void clearAttributes();
};