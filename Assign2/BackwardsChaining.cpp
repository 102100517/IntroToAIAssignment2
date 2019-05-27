
#include "BackwardsChaining.h"

BackwardsChaining::BackwardsChaining(string path): InferenceEngine(path)
{

}

BackwardsChaining::~BackwardsChaining()
{
}

// Entry point for chaining algorithm. Allows for solving multiple arguments
void BackwardsChaining::execute()
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
	// CALL SOLVE SOMEWHERE LOL!
}




bool BackwardsChaining::solve(string arg)
{
	expression result;
	for (auto i = allExpressions.begin(); i != allExpressions.end(); i++)
	{
		
	}
	return false;
}



