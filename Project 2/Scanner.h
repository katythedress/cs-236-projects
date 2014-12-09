#pragma once

#include "Token.h"

#include <vector>

using namespace std;

class Scanner {
	public:
		void scan(ifstream &);
		
		string typeToString(int);
		vector<Token>& getTokens();
		
		void comment(ifstream&);
		void logPunctuation(string);
		void print(ofstream&);

		bool checkForPunctuationInisID(char);

		bool isPunctuation(string, ifstream&);
		bool isACommaPeriodQuestionParen(string);
		void isString(string, ifstream&);
		void isColon(string, ifstream&);
		void isID(char, ifstream&);
		bool isQuoteColon(char, string, string, ifstream&);
		void isSpecial(string);

		bool stringIsSpace(string); // Ghetto "replacement" for the default isspace() function that accepts a string instead of a character

		void logError();
		void printError(int, ofstream&);
};