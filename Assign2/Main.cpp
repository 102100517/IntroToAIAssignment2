#pragma once
#include <iostream>
#include <fstream>
#include "BackwardsChaining.h"
using namespace std;

int main(int argc, char* argv[])
{

	BackwardsChaining* BC = new BackwardsChaining("test_hornKB.txt");
	
	//       ERROR CHECKING
	/*
	if (argc < 3)                      // Check for correct no. of params
	{
		cout << "Too many parameters passed to program" << endl;
		return 0;
	}

	if (myFile.fail())            // Check filename is valid
	{
		cout << "Unable to open file" << endl;
		return 0;
	}

	if ((argv[0] != "FC") || (argv[0] != "BC") || (argv[0] != "TT"))         // Check method name is valid
	{
		cout << "Invalid method name" << endl;
		return 0;
	}
	
	//    IF NO ERRORS OCCUR:

	if (argv[0] == "FC")           // Execute selected method
	{

	}
	else if (argv[0] == "BC")
	{

	}
	else if (argv[0] == "TT")
	{
	
	}
	
	*/
		
	return 0;
}