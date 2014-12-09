#include "Parser.h"

using namespace std;

Parser::Parser(char* arg1, char* arg2) : scan(arg1), t(scan.getToken())
{
	try
	{
		parseDatalog();
	}
	
	catch(Token t)
	{
		ofstream out;
		out.open(arg2);
		out << errorToString();
	}
}

void Parser::parseDatalog()
{
	match(SCHEMES);
	match(COLON);

	if (t.getType() == FACTS)
	{
		error(t);
	}

	parseSchemeList();
	match(FACTS);
	match(COLON);

	if (t.getType() == ID)
	{
		parseFactList();
	}

	match(RULES);
	match(COLON);

	if (t.getType() == ID)
	{
		parseRuleList();
	}

	match(QUERIES);
	match(COLON);
	parseQueryList();
}

void Parser::parseSchemeList()
{
	pr.cleanPredicate();
	parseScheme();
	dp.addScheme(pr);

	if (t.getType() == FACTS)
	{
		return;
	}
	else if (t.getType() == ID)
	{
		parseSchemeList();
	}
	else
	{
		error(t);
	}
}

void Parser::parseScheme()
{
	parsePredicate();
}

void Parser::parseFactList()
{
	pr.cleanPredicate();
	parseFact();
	dp.addFact(pr);

	if(t.getType() == RULES)
	{
		return;
	}
	else if(t.getType() == ID)
	{
		parseFactList();
	}
	else
	{
		error(t);
	}
}

void Parser::parseFact()
{
	parsePredicate();
	match(PERIOD);
}

void Parser::parseRuleList()
{
	r.cleanRule();
	parseRule();
	dp.addRule(r);

	if (t.getType() == QUERIES)
	{
		return;
	}
	else if (t.getType() == ID)
	{
		parseRuleList();
	}
	else
	{
		error(t);
	}
}

void Parser::parseRule()
{
	pr.cleanPredicate();
	parsePredicate();
	r.setHead(pr);
	match(COLON_DASH);
	parsePredicateList();
	match(PERIOD);
}

void Parser::parseQueryList()
{
	pr.cleanPredicate();
	parseQuery();
	dp.addQuery(pr);
	match(Q_MARK);

	if (t.getType() == ID)
	{
		parseQueryList();
	}
	else if (t.getType() == END)
	{
		return;
	}
	else
	{
		error(t);
	}
}

void Parser::parseQuery()
{
	parsePredicate();
}

void Parser::parsePredicateList()
{
	pr.cleanPredicate();
	parsePredicate();
	r.addPredicate(pr);

	if (t.getType() == COMMA)
	{
		match(COMMA);
		parsePredicateList();
	}
}

void Parser::parsePredicate()
{
	pr.setIdentity(t.getValue());
	match(ID);
	match(LEFT_PAREN);
	parseParameterList();
	match(RIGHT_PAREN);
}

void Parser::parseParameterList()
{
	parseParameter();
	pr.addParameter(pm);

	if (t.getType() == COMMA)
	{
		match(COMMA);
		parseParameterList();
	}
}

void Parser::parseParameter()
{
	if (t.getType() == STRING)
	{
		pm.setValue("\'" + t.getValue() + "\'");
		dp.addValue(t.getValue());
		match(STRING);
	}
	else if (t.getType() == ID)
	{
		pm.setValue(t.getValue());
		match(ID);
	}
	else
	{
		error(t);
	}
}

void Parser::match(tokenType k)
{
	if (t.getType() == k)
	{
		t = scan.getToken();
	}
	else
	{
		error(t);
	}
}

void Parser::error(Token t)
{
	throw t;
}

string Parser::errorToString()
{
	stringstream out;
	out << "Failure!\n" << "  " << t.toString();
	return out.str();
}

string Parser::toString()
{
	stringstream out;
	out << "Success!\n" << dp.toString();
	return out.str();
}