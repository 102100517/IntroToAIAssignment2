
#include "BackwardsChaining.h"

BackwardsChaining::BackwardsChaining(string path): InferenceEngine(path)
{
	execute();
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
		solve(*i);
	}

	for (auto i = goals.begin(); i != goals.end(); i++)
	{
		cout << (*i)->name;
		switch ((*i)->value)
		{
		case 0:
			cout << " FALSE, ";
			break;
		case 1:
			cout << " TRUE, ";
			break;
		case 2:
			cout << " UNKNOWN, ";
			break;
		}
		cout << endl;
	}

	for (auto i = allArgs.begin(); i != allArgs.end(); i++)
	{
		if ((*i)->value == TRUE)
		{
			cout << (*i)->name;
			cout << " TRUE, ";
			cout << endl;
		}
	}
	
}


truthValue BackwardsChaining::solve(argument* arg)
{
	// We can never find the value of an operator, attempting to would result in infinite recursion
	if (arg->isOperator()) 
	{
		return FALSE;
	}

	switch (arg->value)
	{
	case truthValue::TRUE:
		return TRUE;

	case truthValue::FALSE:
		return FALSE;

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

		if (toSolve.size() == 0)
		{
			arg->value = FALSE;
			return FALSE; // If no antecedants assume FALSE
		}
			

		for (auto i = toSolve.begin(); i != toSolve.end(); i++)
		{
			if ((*i)->parent == NULL)
			{
				return FALSE; // Prevent a read access violation 
			}

			// Only implication can give us a truth value
			if ((*i)->parent->getName() == "<=>" || (*i)->parent->getName() == "=>") 
			{
				// If we've been given a lhs arg, we need to solve arg->parent->parent->right
				if ((*i) == (*i)->parent->left)
				{
					if (solve((*i)->parent->parent->left->arg) == TRUE)
					{
						arg->value = TRUE;
						return TRUE;
					}
				}
				// Is our antecedant composed of another expression? solve that first
				if ((*i)->parent->left->isOperator())
				{
					if ((*i)->parent->left->getName() == "&")
					{
						// Both operands of the antecedant must return TRUE 
						if ((solve(((*i)->parent->left->left->getArg())) == TRUE && solve(((*i)->parent->left->right->getArg()))) == TRUE)
						{
							arg->value = TRUE;
							return TRUE;
						}
					}
					else if ((*i)->parent->left->getName() == "||")
					{
						// Only one operand must return true
						if ((solve(((*i)->parent->left->left->getArg())) == TRUE || solve(((*i)->parent->left->right->getArg()))) == TRUE)
						{
							arg->value = TRUE;
							return TRUE;
						}
					}
					if (solve((*i)->parent->left->right->getArg()) == TRUE)
					{
						arg->value = TRUE;
						return TRUE;
					}
				}

				if (solve(((*i)->parent->left->getArg())) == TRUE)
				{
				    arg->value = TRUE;
				    return TRUE;
				}
			}

		}

		return FALSE; // if we havent found the value of our param by default return false
	}
	return FALSE;
}



