#pragma once
#include "InferenceEngine.h"

/***********************               CONSTRUCTOR               *********************************/
InferenceEngine::InferenceEngine(string path)
{
	readInFile(path);
	
	list <expression*> result;
	
	for (auto i = allExpressions.begin(); i != allExpressions.end(); i++)
	{
		result.push_back(findWhereConsequent(*i, *goals.begin()));
	}
	
	cout << "";
}

InferenceEngine::~InferenceEngine()
{

}

/*************************************************************************************************/
/**********************             PRIVATE METHODS              *********************************/

expression* InferenceEngine::generateExpression(string sExpression)
{
	argument* arg;
	expression* result, *prevExpression;
	stack <expression*> tree; //
	int bracketCount = 0;
	string name, character;
	string::size_type i = 0;
	character = sExpression[i];

	while (i < sExpression.length()) // Alternate between reading in operators & variables
	{
		if (regex_match(character, rgxVariableChars))
		{
			// Read in an argument until we reach an operator
			while (regex_match(character, rgxVariableChars) && i < sExpression.length())
			{
				name += character;
				i++;
				character = sExpression[i];
			}
		}
		else if (regex_match(character, rgxOperatorChars) && i < sExpression.length())
		{
			// Read in an operator until we reach a variable
			while (regex_match(character, rgxOperatorChars) && i < sExpression.length())
			{
				name += character;
				i++;
				character = sExpression[i];
			}
		}
		else // If it doesnt match keep going
		{
			if (sExpression[i] == '(')
			{
				bracketCount++;
			}
			else if (sExpression[i] == ')')
			{
				bracketCount--;
			}
			i++;
			character = sExpression[i];
		}
		
		if (name == "")
		{
			continue;
		}
		arg = newArg(name); // Create a new argument to point to
		name = "";
		result = new expression(arg);
		 
		
		if (tree.size() > 0) // prevent read access error
		{
			if (tree.top()->isOperator())
			{
				if (tree.size() < 2 && bracketCount > 0)
				{
					tree.push(result);
				}
				else if (bracketCount > 0)
				{
					expression * temp = tree.top();
					tree.pop();
					result->parent = temp;
					temp->right = result;
					temp->parent = tree.top();
					tree.top()->right = temp;
					
				}
				else
				{
					if (!result->setParent(tree.top()))
					{
						tree.top()->setParent(result);
						tree.pop();
						tree.push(result);
					}
				}
			}
			else // Variables need to be made the children of an operator
			{
				tree.top()->setParent(result);
				tree.pop(); // We know we can safely pop at least once due to first IF()

				if (tree.size() > 0 && bracketCount < 1) // Prevent read access error
				{
					tree.top()->setParent(result);
					tree.pop(); // We know we can safely pop at least once due to first IF()
				}

				tree.push(result);
			}
		}
		else // If the stack is empty, add our argument to it
		{
			tree.push(result);
		}
	}

	result = tree.top(); // Only root node remaining
	tree.pop();
	return result;
}

void InferenceEngine::printTree(expression* exp)
{
	if (exp != NULL) // Prevent read access on initial call
	{
		if (exp->left != NULL)  // prevent read access violation on recursive call
		{
			printTree(&*exp->left);
		}
		
		cout << exp->getName() << " ";

		if (exp->right != NULL)   // prevent read access violation on recursive call
		{
			printTree(&*exp->right);
		}
	}
}

// Create a new UNIQUE argument. Else return pointer to already existing copy
argument * InferenceEngine::newArg(string value)
{
	for (auto i = allArgs.begin(); i != allArgs.end(); i++)  
	{
		if ((*i)->name == value)
		{
			return *i; // If an argument already exists don't create a new one
		}
	}
	
	if (value[0] == '~') // Create a positive version just in case it doesnt exist
	{
		newArg(value.substr(1, value.length()));
	}

	argument* result = new argument(value, UNKNOWN);
	allArgs.push_back(result); // Add the new argument to the list of existing ones
	return result;
}


//	Read in the file & push each expression into a list depending on whether we are in ASK or TELL

void InferenceEngine::readInFile(string path)
{
	ifstream myFile;
	myFile.open(path, ios::in);

	if (myFile.is_open())
	{
		bool tell = false;
		char character;
		expression* newExpression;
		argument* newArgument;
		string sExpression; // temporarily holds string value being read in

		while (myFile >> character)   // Extraction operator used over .eof() to prevent read access violations
		{
			if (character == '\n' || character == ';')    // These signal the end of an expression
			{
				if (tell)
				{
					if (regex_match(sExpression, rgxVariableChars)) // If the expression is a standalone variable
					{
						newArgument = newArg(sExpression);
						newArgument->value = TRUE;
						sExpression = "";
					}
					else
					{
						newExpression = generateExpression(sExpression);
						allExpressions.push_back(newExpression);
						sExpression = "";
					}
				}
				else
				{
					newArgument = newArg(sExpression);
					goals.push_back(newArgument);
					sExpression = "";
				}
			}
			else if (!isspace(character))
			{
				sExpression += character;
			}

			if (sExpression == "TELL")
			{
				tell = true;
				sExpression = "";
			}
			else if (sExpression == "ASK")
			{
				tell = false;
				sExpression = "";
			}
		}
		// This block is copied from above to ensure final string is inserted
		// into either list, as the EOF breaks the loop & what is in the remaining expression
		// is ejected
		if (tell && sExpression != "")
		{
			newExpression = generateExpression(sExpression);
			allExpressions.push_back(newExpression);
			sExpression = "";
		}
		else if (sExpression != "")
		{
			newArgument = newArg(sExpression);
			goals.push_back(newArgument);
			sExpression = "";
		}
	}
	else
	{
		cout << "Error opening file\n";
	}
}

/*************************************************************************************************/
/**********************             PROTECTED METHODS             ********************************/

expression * InferenceEngine::findWhereConsequent(expression* source, argument* target)
{
	expression* result = NULL;
	if (source != NULL)
	{
		// If the target is on the left, we need to see if theres an antecedant further up
		if (source->left != NULL && result == NULL)
		{
			if (source->left->getArg() == target)
			{
				// If the parent has no parent no antecedent is possible
				if (source->parent != NULL)
				{
					// Check that the source is not the consequent of its parent
					if (source != source->parent->left)
					{
						return source->left;
					}
				}
			}

			result = findWhereConsequent(source->left, target);
		}

		if (source->right != NULL && result == NULL)
		{
			// name is checked rather than wether they are the same object so that 
			// if an argument is only given in negated form we can still evaluate its positive form
			if (source->right->getArg()->name == target->name) 
			{
				return source->right;
			}
			else
			{
				result = findWhereConsequent(source->right, target);
			}
		}
	}
	return result;
}



/*************************************************************************************************/
/**********************               PUBLIC METHODS              ********************************/

// Entry point for solve method. 
void InferenceEngine::execute()
{

}
/*************************************************************************************************/
















