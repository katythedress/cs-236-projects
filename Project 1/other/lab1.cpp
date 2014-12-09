//============================================================================
// Name        : Lab1.cpp
// Author      : Adam Christiansen
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include "Scanner.h"
#include "Token.h"
//#include "Parser.h"


using namespace std;

//void scanner::scan(ifstream &file_in)
// while(!file_in.eof())

int main(int argc, char* argv[])
{
	ifstream in;
	ofstream out;
	in.open (argv[1]);//("inTemp.txt");//(argv[1]);//("inTemp.txt");//(argv[1]); //("in01.txt"); //(argv[1]);//"in10a.txt");
	out.open (argv[2]);//("outTemp.txt");//(argv[2]);//("outTemp.txt");//(argv[2]); //("out01.txt"); //(argv[4]);//"out10.txt");

	Scanner scanner;
	scanner.scan(in);
	scanner.print(out);

	//for lab 2

//	try
//	{
//		vector<Token>& myTokens = scanner.getTokens();
//		Parser parser;
//
//		parser.parse(myTokens);
//		parser.print(out);
//
//	}
//	catch(Token e)
//	{
//		out << "Failure!" << endl;
//		string myType;
//
//		switch(e.getType())
//		{
//			case(0): myType = "COMMA";
//			break;
//			case(1): myType = "PERIOD";
//			break;
//			case(2): myType = "Q_MARK";
//			break;
//			case(3): myType = "LEFT_PAREN";
//			break;
//			case(4): myType = "RIGHT_PAREN";
//			break;
//			case(5): myType = "COLON";
//			break;
//			case(6): myType = "COLON_DASH";
//			break;
//			case(7): myType = "SCHEMES";
//			break;
//			case(8): myType = "FACTS";
//			break;
//			case(9): myType = "RULES";
//			break;
//			case(10): myType = "QUERIES";
//			break;
//			case(11): myType = "ID";
//			break;
//			case(12): myType = "STRING";
//			break;
//		}
//
//		out << "  (" << myType << ",\"" << e.getData() << "\"," << e.getLine() << ")" << endl;
//	}

	return 0;
}



