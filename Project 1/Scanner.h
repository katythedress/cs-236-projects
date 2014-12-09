#pragma once

#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

class Scanner
{
	private:
		unsigned int currentCharacter; // A ghetto replacement for i in a for loop
		string currentRow; // The current row of the file we're looking at

		string saveSymbol;

		int stringState;
		string saveString;

		string saveID;

		ofstream txt;
		
		int currentLine;
		int tokenCount;

	public:
		Scanner();
		virtual ~Scanner();

		void scan(string loadFile, string saveFile);
		void scanFor();
		void increaseLine();
		void log();

		void logSymbol();

		void logString();
		void clearString();
		void writeString();

		void logID();
		void clearID();
		void writeID();

		void write(string type, string item);
};