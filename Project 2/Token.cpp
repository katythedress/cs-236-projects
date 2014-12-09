#include <iostream>
#include <string>

#include "Token.h"

Token::Token() {
	// Overloaded garbage
}

Token::Token(string d, int l, tokenType t) {
	data = d;
	lineNum = l;
	myType = t;
}

string Token::getData() {
	return data;
}

int Token::getLine() {
	return lineNum;
}

tokenType Token::getType() {
	return myType;
}

string Token::getInfo() {
	string s;
	return s;
}