/*
	

*/
#include <iostream>
#include "BackwardsChaining.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		if (argv[0] == "FC")
		{
		}
		else if (argv[0] == "BC")
		{
		}
		else if (argv[0] == "TT")
		{

		}
		else
		{
			cout << "Invalid method name";
		}
	}
	else
	{
		cout << "Too many parameters passed to program";
	}

	return 0;
}