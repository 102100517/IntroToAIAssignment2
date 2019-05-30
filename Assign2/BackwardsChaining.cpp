
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
			antecedant = findWhereConsequent(*j, *i);

			if (antecedant != NULL)
			{
				toSolve.push_back(antecedant); 
			}
		}
	}
	
}


bool BackwardsChaining::solve(argument* arg)
{
	// We can never find the value of an operator, attempting to would result in infinite recursion
	if (arg->isOperator()) 
	{
		return false;
	}

	switch (arg->value)
	{
	case truthValue::TRUE:
		return true;

	case truthValue::FALSE:
		return false;

	case truthValue::UNKNOWN:

		list <expression*> toSolve; 
		// We need to find all places this variable appears
		for (auto i = allExpressions.begin(); i != allExpressions.end(); i++)
		{
			expression* result = findWhereConsequent(*i, arg); // Get all the 
			if (result != NULL)
			{
				toSolve.push_back(result);
			}
		}

		for (auto i = toSolve.begin(); i != toSolve.end(); i++)
		{
			// If the antecedent implies our argument it can tell us something about our args value
			if ((*i)->parent->getName() == "=>" || (*i)->parent->getName() == "<=>")
			{
				if (!(*i)->isOperator())
				{
					
					if ((*i)->parent->left->arg->value != truthValue::UNKNOWN)
					{
						(*i)->arg->value = (*i)->parent->arg->value;
						
					}
					else
					{
						toSolve.push_back((*i)); // We need to return to this argument
						    
					}
				 
				}




			}
			else
			{
				// If our argument isn't having its value implied then this expression
				// cannot tell us anything about it's truth value
				continue; // See if we can solve it in the next expression
			}
		}
		return false; // if we havent found the value of our param by default return false
		// end of case
	}
	return false;
}



