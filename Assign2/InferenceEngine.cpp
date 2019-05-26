#pragma once
#include "InferenceEngine.h"

/***********************               CONSTRUCTOR               *********************************/
InferenceEngine::InferenceEngine(ifstream &aFile)
{
//	textFile = &aFile;
//	readInFile();
	expression* result = generateExpression("test<=>test2");
	cout << result->arg->name;
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

	string name, character;
	string::size_type i = 0;
	character = sExpression[i];

	while (i < sExpression.length()) // Alternate between reading in operators & variables
	{
		if (regex_match(character, rgxVariableChars))
		{
			while (regex_match(character, rgxVariableChars) && i < sExpression.length())
			{
				name += character;
				i++;
				character = sExpression[i];
			}
		}
		else
		{
			while (regex_match(character, rgxOperatorChars) && i < sExpression.length())
			{
				name += character;
				i++;
				character = sExpression[i];
			}
		}

		arg = newArg(name);
		name = "";
		result = new expression();
		result->arg = arg;
		
		if (tree.size() > 0) // prevent read access error
		{
			if (isOperator(tree.top()->arg))
			{
				result->setParent(tree.top());
			}
			else // Variables need to be made the children of an operator
			{
				result->left = tree.top();
				tree.pop();

				if (tree.size() > 0)
				{
					result->right = tree.top();
					tree.pop();
				}

				tree.push(result);
			}
		}
		else
		{
			tree.push(result);
		}
	}

	result = tree.top();
	tree.pop();
	printTree(result);
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
		
		cout << exp->arg->name << " ";

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

	argument* result = new argument;
	result->name = value;
	result->value = UKNOWN;
	allArgs.push_back(result); // Add the new argument to the list of existing ones
	return result;
}

/*
	Read in the file & push each expression into a list depending on whether we are in ASK or TELL
*/
void InferenceEngine::readInFile()
{
	bool tell = false;
	char character;
	expression* newExpression;
	argument* newGoal;
	string sExpression; // temporarily holds string value being read in

	while (*textFile >> character)   // Extraction operator used over .eof() to prevent read access violations
	{
		if (character == '\n' || character == ';')    // These signal the end of an expression
		{
			if (tell)
			{
				newExpression = generateExpression(sExpression);
				allExpressions.push_back(newExpression);
				sExpression = "";
			}
			else
			{
				newGoal = newArg(sExpression);
				goals.push_back(newGoal);
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
		newGoal = newArg(sExpression);
		goals.push_back(newGoal);
		sExpression = "";
	}
	cout << "";
}

/*************************************************************************************************/
/**********************             PROTECTED METHODS             ********************************/

bool InferenceEngine::isOperator(argument* arg)
{
	if (regex_match(arg->name, rgxOperatorChars))
	{
		return true;
	}
	return false;
}

/*************************************************************************************************/
/**********************               PUBLIC METHODS              ********************************/

// Entry point for solve method. 
void InferenceEngine::execute()
{

}
/*************************************************************************************************/
















