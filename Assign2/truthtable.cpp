#include "truthtable.h"



truthValue truthtable::solve(argument * arg)
{
	if (arg->isOperator())
	{
		return FALSE;
	}
	return truthValue();
}

truthtable::truthtable(string path) : InferenceEngine(path)
{
	execute();
}


truthtable::~truthtable()
{
}

void truthtable::execute()
{
	list <expression*> toSolve;
	string result = "NO: ";
	expression* antecedant;
	for (auto i = allArgs.begin(); i != allArgs.end(); i++)
	{
		if (solve(*i) == TRUE)
		{
			result = "YES: ";
		}
	}
}
