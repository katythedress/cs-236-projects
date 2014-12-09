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
	schemes = p.getDatalog().getSchemes();
	facts = p.getDatalog().getFacts();
	queries = p.getDatalog().getQueries();
	out.open(arg2);
	buildRelations();
	toString();
	out << "Query Evaluation" << endl << endl;
	evalQueries();
	out.close();
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
	for(unsigned int j = 0; j < facts.at(i).getParameterList().size(); j++)
	{
		t.addAttributeValue(facts.at(i).getParameterList().at(j).getValue());
	}
}

bool compare (const Relation& r1, const Relation& r2)
{
	return r1.getName() < r2.getName();
}

void Database::evalQueries()
{
	Relation r;
	map<string, unsigned int> variables;
	map<unsigned int, string> variablePos;

	for (unsigned int i = 0; i < queries.size(); i++)
	{
		if (rels.count(queries.at(i).getIdentity()))
		{
			r = rels.at(queries.at(i).getIdentity());
			
			for (unsigned int j = 0; j < queries.at(i).getParameterList().size(); j++)
			{
				string value = queries.at(i).getParameterList().at(j).getValue();

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
						variablePos.insert(pair<unsigned int, string>(j, value));
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
			r.rename(variablePos);
			r.toString(out);
			out << endl;
		}

		variables.clear();
		variablePos.clear();
	}
}

void Database::toString()
{
	out << "Scheme Evaluation" << endl << endl << "Fact Evaluation" << endl << endl;
	
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