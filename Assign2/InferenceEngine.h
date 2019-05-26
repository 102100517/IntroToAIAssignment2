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
	ifstream* textFile;
	void readInFile();
	expression* generateExpression(string expression); // returns root node of expression
	argument* newArg(string value);
	void printTree(expression* exp);
protected:
	const string orOperator = "||";
	const string andOperator = "&";
	const string impliesOperator = "=>";
	const string biconditionalOperator = "<=>";
	regex rgxOperatorChars = regex("^[<>=&~|]+$"); 
	regex rgxVariableChars = regex("^~?([A-Za-z0-9])+$");
	expression nullExpression;

	list <expression*> allExpressions;   // Expressions stored as pre-processed strings
	list <argument*> allArgs;      // Contains a list of arguments known to be true
	list <argument*> goals;        // Holds aguments to find the truth value of

	
	bool isOperator(argument* arg);


public:
	InferenceEngine(ifstream &myFile);
	~InferenceEngine();
	virtual void execute();
};
