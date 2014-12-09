#include <fstream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Node
{
	private:
		set<string> adjNames;
		unsigned int postOrder;
		bool mark;
		unsigned int num;
		string name;

	public:
		Node();
		
		void addAdjName(string);
		void setName(string);
		void setPostOrder(unsigned int);
		void setNumber(unsigned int);
		unsigned int getNumber() const;
		string getName() const;
		void markVisited();
		unsigned int getPostOrderNumber() const;
		bool visited() const;
		set<string> getAdjNames() const;
		void clearNode();
		string toString();
};