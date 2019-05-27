
#include "BackwardsChaining.h"

BackwardsChaining::BackwardsChaining(string path): InferenceEngine(path)
{
	list <expression*> toSolve;
	expression* antecedant;
	for (auto i = goals.begin(); i != goals.end(); i++)
	{
		for (auto j = allExpressions.begin(); j != allExpressions.end(); j++)
		{
			antecedant = findInExpression(*j, *i);
			
			if (antecedant != NULL)
			{
				toSolve.push_back(antecedant);
			}
		}
	}
	cout << "";
}

BackwardsChaining::~BackwardsChaining()
{
}

// Entry point for chaining algorithm. Allows for solving multiple arguments
void BackwardsChaining::execute()
{
	for (auto iter = goals.begin(); iter != goals.end() ; iter++)
	{
		
	}

}




bool BackwardsChaining::solve(string arg)
{
	
	return false;
}



