#include "TokenType.h"

#include <iostream>

using namespace std;

class Token {
	private:
		tokenType type;
		string value;
		int line;  

	public:
		Token(tokenType, string, int);
		int getLine() const { return line; }
		string getValue() const { return value; }
		tokenType getType() const { return type; }
		string toString() const;
};