#include "Graph.h"

using namespace std;

void Graph::addNode(string name, unsigned int i)
{
	Node n;
	n.setNumber(i);
	stringstream nodeName;
	nodeName << name << i;
	n.setName(nodeName.str());
	nodeList.insert(pair<string, Node>(nodeName.str(), n));
}

void Graph::addAdjacentNode(string n, unsigned int i, string m, unsigned int j)
{
	stringstream key;
	stringstream value;
	key << n << i;
	value << m << j;
	nodeList.at(key.str()).addAdjName(value.str());
}

Node& Graph::getNode(string n, unsigned int i)
{
	stringstream nodeName;
	nodeName << n << i;

	return nodeList.at(nodeName.str());
}

void Graph::dfs(Node& x)
{
	x.markVisited();

	for (auto& name : x.getAdjNames())
	{
		if (!nodeList.at(name).visited())
		{
			dfs(nodeList.at(name));
		}
	}

	x.setPostOrder(currentPostNum);
	orderNodeList.insert(pair<unsigned int, Node>(currentPostNum, x));
	currentPostNum++;
}

map<unsigned int, Node> Graph::getOrderNodeList() const
{
	return orderNodeList;
}

void Graph::clearNodes()
{
	for (auto& Node : nodeList)
	{
		Node.second.clearNode();
	}

	currentPostNum = 1;
	cyclic = false;
	orderNodeList.clear();
}

void Graph::outputPostOrderNumbers(ofstream& out)
{
	out << "Postorder Numbers" << endl;

	for (auto& n : nodeList)
	{
		if (n.second.visited())
		{
			out << "  " << n.first << ": " << n.second.getPostOrderNumber() << endl;
		}
	}
}

void Graph::outputBackEdges(ofstream& out)
{
	out << endl  << "Backward Edges" << endl;
	queue<string> q;

	for (auto& x : nodeList)
	{
		if (x.second.visited())
		{
			for (auto& y : x.second.getAdjNames())
			{
				if (x.second.getPostOrderNumber() <= nodeList.at(y).getPostOrderNumber())
				{
					q.push(y);
				}
			}

			if (q.size() > 0)
			{
				out << "  " << x.first << ":";
				cyclic = true;

				while(q.size() > 0)
				{
					out << " " << q.front();
					q.pop();
				}

				out << endl;
			}
		}
	}

	out << endl;
}

bool Graph::isCyclic()
{
	return cyclic;
}

void Graph::outputRuleEvaluationOrder(ofstream& out)
{
	set<string> printed;
	out << endl << "Rule Evaluation Order" << endl;

	for (auto& x : orderNodeList)
	{
		if (x.second.visited())
		{
			if (!printed.count(x.second.getName()) && x.second.getName().at(0) == 'R')
			{
				printed.insert(x.second.getName());
				out << "  " << x.second.getName() << endl;
			}
		}
	}
}

void Graph::toString(ofstream& out)
{
	out << "Dependency Graph" << endl;

	for (auto& Node : nodeList)
	{
		out << "  " << Node.first << ":" << Node.second.toString() << endl;
	}
}