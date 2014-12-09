#include "Database.h"

using namespace std;

string printd(vector<string> vec)
{
	stringstream out;

	for (unsigned int i = 0; i < vec.size(); i++)
	{
		out << "(" << vec.at(i) << ")" << " ";
	}

	return out.str();
}

Database::Database(char* arg1, char* arg2) : p(arg1, arg2)
{
	size = -1;
	schemes = p.getDatalogProg().getSchemes();
	facts = p.getDatalogProg().getFacts();
	rules = p.getDatalogProg().getRules();
	queries = p.getDatalogProg().getQueries();
	out.open(arg2);
	buildRelations();
	out << "Scheme Evaluation" << endl << endl << "Fact Evaluation" << endl << endl;
	toString();
	buildDependancyGraph();
	dependancyGraph.toString(out);
	out << endl << "Query Evaluation" << endl << endl;
	evaluateQueries();
	out.close();
}

int Database::getSize()
{
	unsigned count = 0;

	for (auto& rel : rels)
	{
		count += rel.second.getTuples().size();
	}

	return count;
}

void Database::buildRelations()
{
	parseSchemes();
	parseFacts();
}

void Database::parseSchemes()
{
	Relation r;

	for (unsigned int i = 0; i < schemes.size(); i++)
	{
		r.setName(schemes.at(i).getIdent());
		setRelationScheme(r, i);
		rels.insert(pair<string, Relation>(r.getName(), r));
		r.clear();
	}
}

void Database::setRelationScheme(Relation& r, unsigned int i)
{
	for (unsigned int j = 0; j < schemes.at(i).getParamList().size(); j++)
	{
		r.addSchemeAttribute(p.getDatalogProg().getSchemes().at(i).getParamList().at(j).getValue());
	}
}

void Database::parseFacts()
{
	Tuple t;

	for (unsigned int i = 0; i < facts.size(); i++)
	{
		if (rels.count(facts.at(i).getIdent()))
		{
			setTupleAttributeValues(t, i);
			rels.at(facts.at(i).getIdent()).addTuple(t);
			t.clear();
		}
	}
}

void Database::setTupleAttributeValues(Tuple& t, unsigned int i)
{
	for(unsigned int j = 0; j < facts.at(i).getParamList().size(); j++)
	{
		t.addAttributeValue(facts.at(i).getParamList().at(j).getValue());
	}
}

void Database::buildDependancyGraph()
{
	for (unsigned int i = 0; i < rules.size(); i++)
	{
		dependancyGraph.addNode("R", i+1);
		vector<Predicate> predList = rules.at(i).getPredList();

		for (unsigned int j = 0; j < rules.size(); j++)
		{
			for (unsigned int k = 0; k < predList.size(); k++)
			{
				if (rules.at(j).getHead().getIdent() == predList.at(k).getIdent())
				{
					dependancyGraph.addAdjacentNode("R", i+1, "R", j+1);
				}
			}
		}

		for (unsigned int j = 0; j < queries.size(); j++)
		{
			dependancyGraph.addNode("Q", j+1);

			if (rules.at(i).getHead().getIdent() == queries.at(j).getIdent())
			{
				dependancyGraph.addAdjacentNode("Q", j+1, "R", i+1);
			}
		}

	}
	
	buildDependancyGraphStuff();
}

void Database::buildDependancyGraphStuff()
{
	if (rules.size() == 0)
	{
		for (unsigned int j = 0; j < queries.size(); j++)
		{
			dependancyGraph.addNode("Q", j+1);
		}
	}
}

bool compare (const Relation& r1, const Relation& r2)
{
	return r1.getName() < r2.getName();
}

void setHeadVariables(vector<string>& schemeAttrs, Relation& r, vector<Parameter>& headParams, string& value,  map<string, unsigned int>& variables, vector<unsigned int>& variablePos, vector<string>& variableNames)
{
	schemeAttrs = r.getScheme().getAttributes();

	for (unsigned int j = 0; j < headParams.size(); j++)
	{
		value = headParams.at(j).getValue();

		for (unsigned int k = 0; k < schemeAttrs.size(); k++)
		{
			if (value == schemeAttrs.at(k))
			{
				variables.insert(pair<string, unsigned int>(value, k));

				if (variables.size() > variablePos.size())
				{
					variableNames.push_back(value);
					variablePos.push_back(k);
				}
			}
		}
	}
}

void forEachParameterSelect(vector<Parameter>& paramList, Relation& r, unsigned int& j, map<string, unsigned int>& variables, vector<unsigned int>& variablePos, vector<string>& variableNames)
{
	string value;

	for (unsigned int k = 0; k < paramList.size(); k++)
	{
		value = paramList.at(k).getValue();

		if (value.at(0) == '\'')
		{
			r.select(k, value);
		}
		else
		{
			if (variables.count(value) > 0)
			{
				r.select(j, variables.at(value));
			}

			variables.insert(pair<string, unsigned int>(value, k));

			if (variables.size() > variablePos.size())
			{
				variableNames.push_back(value);
				variablePos.push_back(k);
			}
		}
	}
}

void Database::evaluateRules()
{
	Relation r;
	map<string, unsigned int> variables;
	vector<unsigned int> variablePos;
	vector<string> variableNames;
	string head;
	vector<Parameter> headParams;
	queue<Relation> intermediate;
	vector<Predicate> predList;
	vector<Parameter> paramList;
	vector<string> schemeAttrs;
	string value;

	for (unsigned int i = 0; i < rulesToEval.size(); i++)
	{
		head = rulesToEval.at(i).getHead().getIdent();
		headParams = rulesToEval.at(i).getHead().getParamList();
		predList = rulesToEval.at(i).getPredList();

		for (unsigned int j = 0; j < predList.size(); j++)
		{
			if (rels.count(predList.at(j).getIdent()))
			{
				r = rels.at(predList.at(j).getIdent());
				paramList = predList.at(j).getParamList();
				forEachParameterSelect(paramList, r, j, variables, variablePos, variableNames);
			}

			r.project(variablePos);
			r.rename(variableNames);
			intermediate.push(r);
			variables.clear();
			variablePos.clear();
			variableNames.clear();
		}

		r = intermediate.front();
		intermediate.pop();

		while (!intermediate.empty())
		{
			r.join(intermediate.front());
			intermediate.pop();
		}

		setHeadVariables(schemeAttrs, r, headParams, value,  variables, variablePos, variableNames);
		r.project(variablePos);
		r.rename(variableNames);
		r.setName(head);

		if (rels.count(r.getName()))
		{
			out << rulesToEval.at(i).toString() << endl;
			rels.at(r.getName()).relationUnion(r, out);
		}

		variables.clear();
		variablePos.clear();
		variableNames.clear();
	}
}


void Database::getRulesToEvaluate()
{
	map<unsigned int, Node> orderNodeList = dependancyGraph.getOrderNodeList();

	for (auto& x : orderNodeList)
	{
		if (x.second.getName().at(0) == 'R')
		{
			int num = x.second.getNumber();
			rulesToEval.push_back(rules.at(num-1));
		}
	}
}

void Database::evaluateQueries()
{
	 for (unsigned int i = 0; i < queries.size(); i++)
	 {
		out << queries.at(i).toString()<< "?" << endl << endl;
		dependancyGraph.dfs(dependancyGraph.getNode("Q", i+1));
		dependancyGraph.outputPostOrderNumbers(out);
		getRulesToEvaluate();
		dependancyGraph.outputRuleEvaluationOrder(out);
		dependancyGraph.outputBackEdges(out);
		out << "Rule Evaluation" << endl;

		if (dependancyGraph.isCyclic())
		{ 
			while (size != getSize())
			{
				size = getSize();
				evaluateRules();
			}
		}
		else
		{ 
			evaluateRules();
		}

		out << endl;
		evalQuery(queries.at(i));
		dependancyGraph.clearNodes();
		rulesToEval.clear();
		size = -1;
	}
}

void Database::toString()
{
	for (auto& rel : rels)
	{
		rel.second.toString(out);
		out << endl;
	}
}

void Database::queryToString(Predicate q, unsigned int numMatches)
{
	out << q.toString() << "? ";

	if (numMatches > 0)
	{
		out << "Yes(" << numMatches << ")" << endl;
	}
	else
	{
		out << "No" << endl << endl;
	}
}

void Database::evalQuery(Predicate q)
{
	Relation r;
	map<string, unsigned int> variables;
	vector<unsigned int> variablePos;
	vector<string> variableNames;
	vector<Parameter> paramList;
	string value;

	if (rels.count(q.getIdent()))
	{
		r = rels.at(q.getIdent());
		paramList = q.getParamList();

		for (unsigned int j = 0; j < paramList.size(); j++)
		{
			value = paramList.at(j).getValue();

			if (value.at(0) == '\'')
			{
				r.select(j, value);
			}
			else
			{
				if (variables.count(value) > 0)
				{
					r.select(j, variables.at(value));
				}

				variables.insert(pair<string, unsigned int>(value, j));

				if (variables.size() > variablePos.size())
				{
					variableNames.push_back(value);
					variablePos.push_back(j);
				}
			}

			r.setName("select");
		}
	}

	queryToString(q ,r.getTuples().size());

	if (r.getTuples().size() > 0)
	{
		r.toString(out);
		r.project(variablePos);
		r.toString(out);
		r.rename(variableNames);
		r.toString(out);
		out << endl;
	}
	
	variables.clear();
	variablePos.clear();
	variableNames.clear();
}