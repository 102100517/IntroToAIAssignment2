#pragma once
#include <regex>
#include <string>
#include <list>
#include <stack>
#include <fstream>
#include <iostream>

#include "Expression.h"

using namespace std;




class InferenceEngine
{
private:
	void readInFile(string path);
	expression* generateExpression(string expression); // returns root node of expression
	argument* newArg(string value);
	void printTree(expression* exp);
protected:
	regex rgxOperatorChars = regex("^[<>=&|]+$");
	regex rgxVariableChars = regex("^[~A-Za-z0-9]+$");
	list <expression*> allExpressions;   // Expressions stored as pre-processed strings
	list <argument*> allArgs;      // Contains a list of arguments known to be true
	list <argument*> goals;        // Holds aguments to find the truth value of

	expression* findWhereConsequent(expression* source, argument* target);
public:
	InferenceEngine(string path);
	~InferenceEngine();
	virtual void execute();
};
