#pragma once
#include <string>
#include "enums.h"
#include <regex>
using namespace std;


class argument
{
public:
	argument(string pName, truthValue pValue);
	~argument();

	string name;
	truthValue value;
	bool isOperator();

private:
	regex rgxOperatorChars = regex("^[<>=&|]+$");
};

