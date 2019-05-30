#include "argument.h"



argument::argument(string pName, truthValue pValue)
{
	name = pName;
	value = pValue;
}


argument::~argument()
{
}

bool argument::isOperator()
{
		if (regex_match(name, rgxOperatorChars))
		{
			return true;
		}
		return false;
}
