#include "Scanner.h"

using namespace std;

Scanner::Scanner()
{
	currentCharacter = 0;
	stringState = 0;
	currentLine = 0;
	tokenCount = 0;
}

Scanner::~Scanner(){}

void Scanner::scanFor() // Ghetto complexity limit
{
	if (stringState == 0 && currentRow[currentCharacter] == '\'' && currentRow[currentCharacter + 1] == '\'')
	{
		Scanner::write("STRING", "");
		currentCharacter++;
	}
	else
	{
		Scanner::log();
	}
}

void Scanner::scan(string loadFile, string saveTo) // Set up a bit funky to allow for command line arguments
{
	try
	{
		ifstream file(loadFile); // Load the file to read
		ofstream outputFile(saveTo); // Load the file to save to
		txt.open(saveTo);

		while (getline(file, currentRow))
		{
			Scanner::increaseLine();

			for (currentCharacter = 0; currentCharacter <= currentRow.length(); currentCharacter++)
			{
				if (currentRow[currentCharacter] == '#' && stringState != 1) // If we hit a pound sign that's not part of a string
				{
					break;
				}
				else
				{
					Scanner::scanFor();
				}
			}
		}

		txt << "Total Tokens = " << tokenCount;

		cout << "! File with " << currentLine << " line(s) parsed and saved" << endl;
	}
	catch (int e) // "Global" error catching
	{
		switch(e)
		{
			case 0: // General syntax error
				cout << "! Input error on line " << currentLine << endl;
				txt << "Input error on line " << currentLine << endl;
				break;
			case 1: // Incomplete string
				cout << "! Incomplete string" << endl;
				txt << "Input error on line " << currentLine << endl;
				break;
		}
	}
}

void Scanner::increaseLine()
{
	currentLine++;
	Scanner::clearString();
	Scanner::clearID();
}

void Scanner::log()
{
	if (!currentRow.empty()) // If the row isn't empty
	{
		switch(stringState)
		{
			case 0:
				switch(currentRow[currentCharacter])
				{
					case '\'':
						Scanner::writeID();
						stringState = 1;
						break;
					case ',':
						Scanner::writeID();
						Scanner::write("COMMA", ",");
						break;
					case '.':
						Scanner::writeID();
						Scanner::write("PERIOD", ".");
						break;
					case '?':
						Scanner::writeID();
						Scanner::write("Q_MARK", "?");
						break;
					case '(':
						Scanner::writeID();
						Scanner::write("LEFT_PAREN", "(");
						break;
					case ')':
						Scanner::writeID();
						Scanner::write("RIGHT_PAREN", ")");
						break;
					case ':':
						Scanner::writeID();
						Scanner::logSymbol();
						break;
					case '-':
						Scanner::writeID();
						Scanner::logSymbol();
						break;
					case ' ': case '\n': case '\r':
						Scanner::writeID();
						break;
					/*
					case '\n': case '\r':
						break; // Stupid new lines
					*/
					default:
						Scanner::logID();
				}
				break;
			case 1: // If we're building a string
				// cout << "In string building mode " << currentRow[currentCharacter] << endl;

				switch(currentRow[currentCharacter])
				{
					case '\'':
						Scanner::writeString();
						break;
					default:
						Scanner::logString();
				}
				break;
		}
	}
}

void Scanner::logSymbol()
{
	if (currentRow[currentCharacter] == ':' && currentRow[currentCharacter + 1] == '-')
	{
		Scanner::write("COLON_DASH", ":-");
	}
	else if (currentRow[currentCharacter] == ':')
	{
		Scanner::write("COLON", ":");
	}
}

void Scanner::logString()
{
	if (isalnum(currentRow[currentCharacter]) || ispunct(currentRow[currentCharacter]) || currentRow[currentCharacter] == ' ' || currentRow[currentCharacter] == '\t')
	{
		saveString += currentRow[currentCharacter];
	}
	else
	{
		throw(1);
	}
}

void Scanner::clearString()
{
	saveString.clear();
	stringState = 0;
}

void Scanner::writeString()
{
	if (saveString.length() > 0)
	{
		Scanner::write("STRING", saveString);
		Scanner::clearString();
	}
}

void Scanner::logID()
{
	// cout << "INSIDE logID() {" << currentRow[currentCharacter] << "}" << endl;

	if (!isspace(currentRow[currentCharacter]))
	{
		if (saveID.length() == 0)
		{
			if (isalpha(currentRow[currentCharacter])) // Check for invalid characters
			{
				saveID += currentRow[currentCharacter];
			}
			else if (isdigit(currentRow[currentCharacter]) || ispunct(currentRow[currentCharacter]))
			{
				throw(0);
			}
		}
		else
		{
			if (isalnum(currentRow[currentCharacter]))
			{
				saveID += currentRow[currentCharacter];
			}
			else
			{
				Scanner::writeID();
			}
		}
	}
}

void Scanner::clearID()
{
	saveID.clear();
}

void Scanner::writeID()
{
	// cout << saveID << endl;

	if (saveID.length() > 0)
	{
		if (saveID == "Schemes")
		{
			Scanner::write("SCHEMES", "Schemes");
		}
		else if (saveID == "Facts")
		{
			Scanner::write("FACTS", "Facts");
		}
		else if (saveID == "Rules")
		{
			Scanner::write("RULES", "Rules");
		}
		else if (saveID == "Queries")
		{
			Scanner::write("QUERIES", "Queries");
		}
		else
		{
			Scanner::write("ID", saveID);
		}

		Scanner::clearID();
	}
}

void Scanner::write(string type, string i)
{	
	cout << "(" << type << ",\"" << i << "\"," << currentLine << ")" << endl; // Debug

	txt << "(" << type << ",\"" << i << "\"," << currentLine << ")" << endl;
	tokenCount++;
}