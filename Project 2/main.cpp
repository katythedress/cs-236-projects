#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	ifstream in;
	ofstream out;
	in.open (argv[1]);
	out.open (argv[2]);

	Scanner scanner;
	scanner.scan(in);

	try
	{
		vector<Token>& tokens = scanner.getTokens();
		Parser parser;

		parser.parse(tokens);
		parser.print(out);

	}
	catch(Token e) // "Global" error catching
	{
		out << "Failure!" << endl;
		string myType;

		switch(e.getType())
		{
			case(0):
				myType = "COMMA";
				break;
			case(1):
				myType = "PERIOD";
				break;
			case(2):
				myType = "Q_MARK";
				break;
			case(3):
				myType = "LEFT_PAREN";
				break;
			case(4):
				myType = "RIGHT_PAREN";
				break;
			case(5):
				myType = "COLON";
				break;
			case(6):
				myType = "COLON_DASH";
				break;
			case(7):
				myType = "SCHEMES";
				break;
			case(8):
				myType = "FACTS";
				break;
			case(9):
				myType = "RULES";
				break;
			case(10):
				myType = "QUERIES";
				break;
			case(11):
				myType = "ID";
				break;
			case(12):
				myType = "STRING";
				break;
			default:
				break;
		}

		out << "  (" << myType << ",\"" << e.getData() << "\"," << e.getLine() << ")" << endl;
	}

	return 0;
}