#include "Node.h"

using namespace std;

Node::Node()
{
	postOrder = 0;
	mark = false;
	num = 0;
	name = "";
}

void Node::addAdjName(string n)
{
	adjNames.insert(n);
}

void Node::setName(string n)
{
	name = n;
}

void Node::setPostOrder(unsigned int n)
{
	postOrder = n;
}

void Node::setNumber(unsigned int n)
{
	num = n;
}

unsigned int Node::getNumber() const
{
	return num;
}

void Node::markVisited()
{
	mark = true;
}

unsigned int Node::getPostOrderNumber() const
{
	return postOrder;
}

bool Node::visited() const
{
	return mark;
}

set<string> Node::getAdjNames () const
{
	return adjNames;
}

string Node::getName() const
{
	return name;
}

void Node::clearNode()
{
	postOrder = 0;
	mark = false;
}

string Node::toString()
{
	stringstream out;

	for (auto& name : adjNames)
	{
		out << " " << name;
	}
	
	return out.str();
}