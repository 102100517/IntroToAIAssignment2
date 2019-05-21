#pragma once
#include <iostream>
#include <fstream>
#include "BackwardsChaining.h"
using namespace std;

int main(int argc, char* argv[])
{
	ifstream myFile;
	myFile.open("../test_genericKB.txt", ios::in);

	if (myFile.is_open())
	{
		BackwardsChaining* BC = new BackwardsChaining(myFile);
	}
	
	myFile.close();
	
	/*

	if (argc < 3)                      // Check for correct no. of params
	{
		cout << "Too many parameters passed to program";
	}
	else if (myFile.fail())            // Check filename is valid
	{
		cout << "Unable to open file";
	}
	else if ((argv[0] != "FC") || (argv[0] != "BC") || (argv[0] != "TT"))         // Check method name is valid
	{

		if (argv[0] == "FC")           // Execute selected method
		{

		}
		else if (argv[0] == "BC")
		{

		}
		else if (argv[0] == "TT")
		{

		}
	}
		*/
	return 0;
}