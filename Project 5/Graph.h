#include "Node.h"

#include <map>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
	private:
		map<string, Node> nodeList;
		unsigned int currentPostNum = 1;
		bool cyclic = false;
		map<unsigned int, Node> orderNodeList;
		
	public:
		void addNode(string, unsigned int);
		void addAdjacentNode(string, unsigned int, string, unsigned int);
		Node& getNode(string, unsigned int);
		map<unsigned int, string> getPostOrderList() const;
		map<unsigned int, Node> getOrderNodeList() const; 
		void dfs(Node&);
		void clearNodes();
		void outputPostOrderNumbers(ofstream&);
		void outputBackEdges(ofstream&);
		bool isCyclic();
		void outputRuleEvaluationOrder(ofstream&);
		void toString(ofstream&);
};