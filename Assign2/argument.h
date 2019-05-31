#pragma once
#include <string>
#include "enums.h"
#include <regex>
using namespace std;

//Changing to argument class instead of a struct
class argument
{
public:
	//constructor taking in a name and a enum value
	argument(string pName, truthValue pValue);
	//destructor
	~argument();

	//name of the argument
	string name;
	//enum value either TRUE/FALSE/UNKNOWN
	truthValue value;
	//If this is an operator or an actual argument
	bool isOperator();
	//returns the opposite of the value to check for negation
	bool isNegated();
private:
	//checking if its an operator or an actual argument
	regex rgxOperatorChars = regex("^[<>=&|]+$");
	//if its a negated value.
	bool negated;
};

