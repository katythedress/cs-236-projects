#include "Halp.h"
#include "Scanner.h"
#include "Token.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<Token> tokenDatabase;

string data;
string type;
int line = 1;

bool error = false;
int errorLineNumber = 0;

void Scanner::scan(ifstream& fileIn)
{
	while (!fileIn.eof()) // While we're not at the end of the file...
	{
		char e = fileIn.get();
		data += e;

		if (data == "\n")
		{
			line++;
			data.clear();
		}
		else if (isPunctuation(data, fileIn))
		{
			data.clear();
		}
		else if (isalpha(e))
		{
			isID(e, fileIn);
			data.clear();
		}
		else if (isspace(e))
		{
			data.clear();
		}
		else if (e == -1)
		{
			data.clear();
			break;
		}
		else
		{
			logError();
			data.clear();
		}
	}
}

void Scanner::logError()
{
	error = true;

	if (errorLineNumber == 0)
	{
		errorLineNumber = line;
	}
}

bool Scanner::isPunctuation(string data, ifstream& fileIn)
{
	if (isACommaPeriodQuestionParen(data))
	{
		logPunctuation(data);
		data.clear();
		return true;
	}
	else if (data == ":")
	{
		isColon(data, fileIn);
		data.clear();
		return true;
	}
	else if (data == "'")
	{
		isString(data, fileIn);
		data.clear();
		return true;
	}
	else if (data == "#")
	{
		comment(fileIn);
		data.clear();
		return true;
	}
	else
	{
		return false;
	}
}

bool Scanner::isACommaPeriodQuestionParen(string data)
{
	if (data == "," || data == "." || data == "?" || data == "(" || data == ")")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Scanner::logPunctuation(string info)
{
	string data = info;
	Token newToken;

	if (data == ",")
	{
		newToken = Token(data, line, COMMA);
	}
	else if (data == ".")
	{
		newToken = Token(data, line, PERIOD);
	}
	else if (data == "?")
	{
		newToken = Token(data, line, Q_MARK);
	}
	else if (data == "(")
	{
		newToken = Token(data, line, LEFT_PAREN);
	}
	else if (data == ")")
	{
		newToken = Token(data, line, RIGHT_PAREN);
	}

	tokenDatabase.push_back(newToken);
}

void Scanner::print(ofstream &file_out)
{
	string t;

	for (size_t i = 0; i < tokenDatabase.size(); i++)
	{
		t = typeToString(tokenDatabase.at(i).getType());
		file_out << "(" << t << +",\"" << tokenDatabase.at(i).getData() << +"\"," << tokenDatabase.at(i).getLine() << +")" << endl;
	}
	
	if (error == false)
	{
		file_out << "Total Tokens = " << tokenDatabase.size() << endl;
	}
	else
	{
		printError(errorLineNumber, file_out);
		tokenDatabase.clear();
	}
}

void Scanner::isString(string s, ifstream&in)
{
	string data;
	char c;
	bool t = true;

	while (t)
	{
		c = in.get();
		if (c == '\'')
		{
			Token newToken(data, line, STRING);
			tokenDatabase.push_back(newToken);
			t = false;
		}
		else if (c == '\n' || c == -1)
		{
			logError();
			t = false;
		}
		else
		{
			data += c;
		}
	}
}

void Scanner::isColon(string s, ifstream &in)
{
	string data = s;
	char c = in.peek();
	Token newToken;

	if (c == '-')
	{
		c = in.get();
		data += c;
		newToken = Token(data, line, COLON_DASH);
	}
	else
	{
		newToken = Token(data, line, COLON);
	}

	tokenDatabase.push_back(newToken);
}

void Scanner::printError(int l, ofstream &file_out)
{
	if (error == true)
	{
		file_out << "Input Error on line " << l << endl;
		tokenDatabase.clear();
	}
}

void Scanner::isID(char c, ifstream& in)
{
	char value = c;
	string data, temp;
	bool t = true;

	data += value;

	while (t)
	{
		value = in.get();

		if (isalnum(value))
		{
			data += value;
		}
		else if (isspace(value))
		{
			isSpecial(data);
			data.clear();

			if (value == '\n') {
				line++;
			}
			t = false;
		}
		else if (checkForPunctuationInisID(value))
		{
			isSpecial(data);
			data.clear();
			temp += value;
			logPunctuation(temp);
			temp.clear();
		}
		else if (isQuoteColon(value, data, temp, in))
		{
			data.clear();
			temp.clear();
		}
		else if (value == -1)
		{
			isSpecial(data);
			data.clear();
			t = false;
		}
		else
		{
			isSpecial(data);
			logError();
			t = false;
		}
	}
}

bool Scanner::checkForPunctuationInisID(char data)
{
	if (data == ',' || data == '.' || data == '?' || data == '(' || data == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scanner::isQuoteColon(char value, string data, string temp, ifstream& in)
{
	if (value == '\'')
	{
		isSpecial(data);
		data.clear();
		temp += value;
		isString(temp, in);
		temp.clear();
		return true;
	}
	else if (value == ':')
	{
		isSpecial(data);
		data.clear();
		temp += value;
		isColon(temp, in);
		temp.clear();
		return true;
	}
	else
	{
		return false;
	}
}

void Scanner::isSpecial(string s)
{
	if (error == false) {
		string data = s;

		if (data == "Schemes")
		{
			Token newToken(data, line, SCHEMES);
			tokenDatabase.push_back(newToken);
			data.clear();
		}
		else if (data == "Facts")
		{
			Token newToken(data, line, FACTS);
			tokenDatabase.push_back(newToken);
			data.clear();
		}
		else if (data == "Rules")
		{
			Token newToken(data, line, RULES);
			tokenDatabase.push_back(newToken);
			data.clear();
		}
		else if (data == "Queries")
		{
			Token newToken(data, line, QUERIES);
			tokenDatabase.push_back(newToken);
			data.clear();
		}
		else if (stringIsSpace(data)) // Wow, this is ghetto
		{
			// Wha...?
		}
		else
		{
			Token newToken(data, line, ID);
			tokenDatabase.push_back(newToken);
			data.clear();
		}
	}
}

bool Scanner::stringIsSpace(string data)
{
	if (data == "\n" || data == "\t" || data == "" || data == " ")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Scanner::comment(ifstream &in)
{
	char c = in.get();
	bool t = true;

	while (t)
	{
		if (c == '\n' || c == -1)
		{
			if (c == '\n')
			{
				line++;
			}
			
			t = false;
		}
		else
		{
			c = in.get();
		}
	}
}

string Scanner::typeToString(int t)
{
	string type;

	switch (t)
	{
		case 0:
			type = "COMMA";
			return type;
		case 1:
			type = "PERIOD";
			return type;
		case 2:
			type = "Q_MARK";
			return type;
		case 3:
			type = "LEFT_PAREN";
			return type;
		case 4:
			type = "RIGHT_PAREN";
			return type;
		case 5:
			type = "COLON";
			return type;
		case 6:
			type = "COLON_DASH";
			return type;
		case 7:
			type = "SCHEMES";
			return type;
		case 8:
			type = "FACTS";
			return type;
		case 9:
			type = "RULES";
			return type;
		case 10:
			type = "QUERIES";
			return type;
		case 11:
			type = "ID";
			return type;
		case 12:
			type = "STRING";
			return type;
		default:
			type = "WTF";
			return type;
	}
}

vector<Token>& Scanner::getTokens()
{
	return tokenDatabase;
}