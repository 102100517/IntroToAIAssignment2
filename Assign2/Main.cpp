#pragma once
#include <iostream>
#include <fstream>
#include "BackwardsChaining.h"
#include "ForwardsChaining.h"
using namespace std;

int main(int argc, char* argv[])
{

	
	
	if (argc != 3)                      // Check for correct no. of params
	{
		cout << "Incorrect no. of parameters passed" << endl;
		return 0;
	}

	cout << argv[1] << endl;

	if (strcmp(argv[1], "FC"))           // Execute selected method
	{
		ForwardsChaining* FC = new ForwardsChaining(argv[2]);
	}
	else if (strcmp(argv[1], "BC"))
	{

		BackwardsChaining* BC = new BackwardsChaining(argv[2]);
	}
	else if (strcmp(argv[1], "TT"))
	{
		// NOT IMPLEMENTED
	}
	else
	{
		cout << "Invalid method name" << endl;
		return 0;
	}
	
	
		
	return 0;
}