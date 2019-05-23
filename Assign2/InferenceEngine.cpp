#pragma once
#include "InferenceEngine.h"

InferenceEngine::InferenceEngine(ifstream &aFile)
{
	textFile = &aFile;
	readInFile();

}

InferenceEngine::~InferenceEngine()
{

}

void InferenceEngine::execute()
{
	list <string> YEET;

	for (auto iter = goals.begin(); iter != goals.end(); iter++)
	{
		YEET = findInExpression(*iter); // Retrieve all the args relevant to this

		for (auto yeeter = YEET.begin(); yeeter != YEET.end(); yeeter++)
		{

		}
	}
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

// Return the expression containing the argument we want to evaluate
list <string> InferenceEngine::findInExpression(string arg)
{
	list <string> result;

	for (auto iter = expressions.begin(); iter != expressions.end(); iter++)
	{
		if ((*iter).find(arg) != string::npos) // .find() returns position of substring, npos means end of the string
		{
			result.push_back(*iter); // Its inside the goal!
		}
	}
	return result; // We found nothing
}






