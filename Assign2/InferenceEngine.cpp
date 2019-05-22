
#pragma once
#include "InferenceEngine.h"

InferenceEngine::InferenceEngine(ifstream &aFile)
{
	textFile = &aFile;
	readInFile();
	
	cout << getAntecedant("a") << endl;
	cout << getAntecedant("b") << endl;
	cout << getAntecedant("returnFalse") << endl;
}

InferenceEngine::~InferenceEngine()
{

}

/* 
    Read in the file & push each expression into a list depending on whether we are in ASK or TELL
*/
void InferenceEngine::readInFile()
{
	char text;
	string expression;
	list<string>* destination = &expressions;     // We assume ASK first

	while (*textFile >> text)               // Extraction operator used over .eof() to prevent read access violations
	{
		if (text == '\n' || text == ';')    // These signal the end of an expression
		{
			destination->push_back(expression);
			expression = "";                // Push finished expression, reset for new one
		}
		else if (!isspace(text))
		{
			expression += text;
		}

		if (expression == "TELL")
		{
			destination = &expressions;
			expression = "";                // Reset string as no ; or \n after TELL
		}
		else if (expression == "ASK")
		{
			destination = &knownFacts;
			expression = "";                // Reset string as no ; or \n after ASK
		}

	}
	destination->push_back(expression);     // If no colon at the end of the final expression it may be missed
}

// Find an argument in an expression, then grab the antecedent to its LEFT
string InferenceEngine::getAntecedant(string arg)
{
	string argument = getContainingArgument(arg); // Do any of our goals contain the argument?
	
	if (argument == "")    // NO, exit & try another argument
	{
		return "";
	}

	string::size_type position = argument.find_first_of(arg);  // Find the position of the argument in the string
	position--;          // Previous character should be an operand
	string result = arg; // Our result is the argument we're looking for + an operator and its antecedant

	if (argument[position] == '~')
	{
		result.insert(result.begin(), argument[position]);
		position--;      // if our arg is negated the operator is behind the negation
	}
	position = -34;

	result[position];
	return result;	
}

// Return the expression containing the argument we want to evaluate
string InferenceEngine::getContainingArgument(string arg)
{
	for (auto iter = expressions.begin(); iter != expressions.end(); iter++)
	{
		if ((*iter).find(arg) != string::npos) // .find() returns position of substring, npos means end of the string
		{
			return *iter; // Its inside the goal!
		}
	}
	return ""; // We found nothing
}






