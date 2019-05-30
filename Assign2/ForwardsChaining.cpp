#include "ForwardsChaining.h"

ForwardsChaining::ForwardsChaining(string path): InferenceEngine(path)
{
	execute();
}


ForwardsChaining::~ForwardsChaining()
{
}

void ForwardsChaining::execute()
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

	cout << result;

	for (auto i = allArgs.begin(); i != allArgs.end(); i++)
	{
		if ((*i)->value == TRUE)
		{
			if ((*i)->isNegated())
			{
				cout << "~";
			}
			cout << (*i)->name << ",";
		}
	}
}


truthValue ForwardsChaining::solve(argument * arg)
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
				if ((*i) == (*i)->parent->right)
				{
					if (solve((*i)->parent->parent->right->arg) == TRUE)
					{
						arg->value = TRUE;
						return TRUE;
					}
				}
				// Is our consequent composed of another expression? solve that first
				if ((*i)->parent->right->isOperator())
				{
					if ((*i)->parent->right->getName() == "&")
					{
						// Both operands of the antecedant must return TRUE 
						if ((solve(((*i)->parent->right->right->getArg())) == TRUE && solve(((*i)->parent->right->left->getArg()))) == TRUE)
						{
							arg->value = TRUE;
							return TRUE;
						}
					}
					else if ((*i)->parent->right->getName() == "||")
					{
						// Only one operand must return true
						if ((solve(((*i)->parent->right->right->getArg())) == TRUE || solve(((*i)->parent->right->left->getArg()))) == TRUE)
						{
							arg->value = TRUE;
							return TRUE;
						}
					}
					if (solve((*i)->parent->right->left->getArg()) == TRUE)
					{
						arg->value = TRUE;
						return TRUE;
					}
				}

				if (solve(((*i)->parent->right->getArg())) == TRUE)
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
