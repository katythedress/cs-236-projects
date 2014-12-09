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
	schemes = p.getDatalog().getSchemes();
	facts = p.getDatalog().getFacts();
	rules = p.getDatalog().getRules();
	queries = p.getDatalog().getQueries();
	out.open(arg2);
	buildRelations();
	out << "Scheme Evaluation" << endl << endl << "Fact Evaluation" << endl << endl;
	toString();
	out << "Rule Evaluation" << endl << endl;
	unsigned int i = 0;

	while (size != getSize())
	{
		i++;
		size = getSize();
		evaluateRules();
	}

	out << endl << "Converged after " << i << " passes through the Rules." << endl << endl;
	toString();
	out << "Query Evaluation" << endl << endl;
	evaluateQueries();
	out.close();
}

unsigned int Database::getSize()
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
		r.setName(schemes.at(i).getIdentity());
		setRelationScheme(r, i);
		rels.insert(pair<string, Relation>(r.getName(), r));
		r.clear();
	}
}

void Database::setRelationScheme(Relation& r, unsigned int i)
{
	for (unsigned int j = 0; j < schemes.at(i).getParameterList().size(); j++)
	{
		r.addSchemeAttribute(p.getDatalog().getSchemes().at(i).getParameterList().at(j).getValue());
	}
}

void Database::parseFacts()
{
	Tuple t;

	for (unsigned int i = 0; i < facts.size(); i++)
	{
		if (rels.count(facts.at(i).getIdentity()))
		{
			setTupleAttributeValues(t, i);
			rels.at(facts.at(i).getIdentity()).addTuple(t);
			t.clear();
		}
	}
}

void Database::setTupleAttributeValues(Tuple& t, unsigned int i)
{
	for (unsigned int j = 0; j < facts.at(i).getParameterList().size(); j++)
	{
		t.addAttributeValue(facts.at(i).getParameterList().at(j).getValue());
	}
}

bool compare (const Relation& r1, const Relation& r2)
{
	return r1.getName() < r2.getName();
}

void forEachParameterSelect(vector<Parameter>& paramList, Relation& r, unsigned int& j, map<string, unsigned int>& variables, vector<unsigned int>& variablePos, vector<string>& variableNames)
{
	string value;

	for(unsigned int k = 0; k < paramList.size(); k++)
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

	for (unsigned int i = 0; i < rules.size(); i++)
	{
		head = rules.at(i).getHead().getIdentity();
		headParams = rules.at(i).getHead().getParameterList();
		predList = rules.at(i).getPredicateList();

		for (unsigned int j = 0; j < predList.size(); j++)
		{
			if (rels.count(predList.at(j).getIdentity()))
			{
				r = rels.at(predList.at(j).getIdentity());
				paramList = predList.at(j).getParameterList();
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
		rules.at(i).toString();
		r.setName(head);

		if (rels.count(r.getName()))
		{
			out << rules.at(i).toString() << endl;
			rels.at(r.getName()).relationUnion(r, out);
		}

		variables.clear();
		variablePos.clear();
		variableNames.clear();
	}
}

void Database::evaluateQueries()
{
	Relation r;
	map<string, unsigned int> variables;
	vector<unsigned int> variablePos;
	vector<string> variableNames;
	vector<Parameter> paramList;
	string value;

	for (unsigned int i = 0; i < queries.size(); i++)
	{
		if (rels.count(queries.at(i).getIdentity()))
		{
			r = rels.at(queries.at(i).getIdentity());
			paramList = queries.at(i).getParameterList();

			for(unsigned int j = 0; j < paramList.size(); j++)
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

		queryToString(i ,r.getTuples().size());

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
}

void Database::toString()
{
	for (auto& rel : rels)
	{
		rel.second.toString(out);
		out << endl;
	}
}

void Database::queryToString(unsigned int i, unsigned int numMatches)
{
	out << queries.at(i).toString() << "? ";

	if (numMatches > 0)
	{
		out << "Yes(" << numMatches << ")" << endl;
	}
	else
	{
		out << "No" << endl << endl;
	}
}