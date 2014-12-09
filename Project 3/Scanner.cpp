#include "Scanner.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Scanner::Scanner(char* arg)
{
	line = 1;
	error = false;
	readFile(arg);
	readTokens();
	tokens.push(Token(END, "End", line));
}

void Scanner::readFile(char* arg)
{
	ifstream in;
	in.unsetf(ios_base::skipws);
	in.open(arg);
	char c;

	while (in >> c)
	{
		code.push(c);
	}

	in.close();
}

void Scanner::readTokens()
{
	while (!code.empty() && !error)
	{
		switch (code.front())
		{
			case ',':
				tokens.push(Token(COMMA,",",line));
				code.pop();
				break;
			case '.':
				tokens.push(Token(PERIOD,".",line));
				code.pop();
				break;
			case '?':
				tokens.push(Token(Q_MARK,"?",line));
				code.pop();
				break;
			case '(':
				tokens.push(Token(LEFT_PAREN,"(",line));
				code.pop();
				break;
			case ')':
				tokens.push(Token(RIGHT_PAREN,")",line));
				code.pop();
				break;
			case ':': // Also handles :-
				scanColon(); 
				break;
			case '\'':
				scanString();
				break;
			case '#':
				scanComment();
				break;
			case '\n':
				scanNewline();
				break;
			case ' ':
				code.pop();
				break;
			case '\t':
				code.pop();
				break;
			default:
				if(!isalnum(code.front())) {
					scanError();
					error = true;
				}
				else
				{
					scanIdentity();
				}
		}
	}
}

void Scanner::scanColon()
{
	code.pop();
	
	if (code.front() == '-')
	{
		tokens.push(Token(COLON_DASH,":-",line));
		code.pop();
	}
	else
	{
		tokens.push(Token(COLON,":",line));
	}
}

void Scanner::scanString()
{
	code.pop();
	stringstream s;

	while (code.front() != '\'')
	{
		if (code.empty() || code.front() == '\n')
		{
			error = true;
			scanError();
			return;
		}

		s << code.front();
		code.pop();
	}

	tokens.push(Token(STRING, s.str(), line));
	code.pop();
}

void Scanner::scanError()
{
	tokens.push(Token(ERROR,"Input Error on line ",line));
}

void Scanner::scanIdentity()
{
	stringstream s;

	if (isdigit(code.front()))
	{
		error = true;
		scanError();
		return;
	}

	while (isalnum(code.front()))
	{
		s << code.front();
		code.pop();
	}

	if (s.str() == "Schemes")
	{
		tokens.push(Token(SCHEMES, s.str(), line));
	}
	else if (s.str() == "Facts")
	{
		tokens.push(Token(FACTS, s.str(), line));
	}
	else if (s.str() == "Rules")
	{
		tokens.push(Token(RULES, s.str(), line));
	}
	else if (s.str() == "Queries")
	{
		tokens.push(Token(QUERIES, s.str(), line));
	}
	else
	{
		tokens.push(Token(ID, s.str(), line));
	}
}

void Scanner::scanComment()
{
	while(code.front() != '\n')
	{
		code.pop();
	}

	code.pop();
	line += 1;
}

void Scanner::scanNewline()
{
	code.pop();
	line += 1;
}

Token Scanner::getToken()
{
	Token t = tokens.front();
	tokens.pop();
	return t;
}

string Scanner::tokensToString()
{
	int numTokens = 0;
	stringstream out;

	while (!tokens.empty())
	{
		if (tokens.front().getType() == ERROR)
		{
			out << "Input Error on line " << line;
			break;
		}

		out << tokens.front().toString();
		tokens.pop();
		numTokens += 1;
	}
	
	if(!error)
	{
		out << "Total Tokens = " << numTokens;
	}

	return out.str();
}