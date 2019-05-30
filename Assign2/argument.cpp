#include "argument.h"



argument::argument(string pName, truthValue pValue)
{
	name = pName;
	value = pValue;

	if (name[0] == '~')
	{
		negated = true;
		name = name.substr(1, name.length() - 1);
	}
	else
	{
		negated = false;
	}

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

bool argument::isNegated()
{
	if (negated)
	{
		return true;
	}

	return false;
}
