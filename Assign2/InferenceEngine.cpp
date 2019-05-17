#include "InferenceEngine.h"
#include <string>


InferenceEngine::InferenceEngine(ifstream &aFile)
{
	textFile = &aFile;
	readInFile();
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
	list<string>* destination = &goals;     // We assume ASK first

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
			destination = &facts;
			expression = "";                // Reset string as no ; or \n after TELL
		}
		else if (expression == "ASK")
		{
			destination = &goals;
			expression = "";                // Reset string as no ; or \n after ASK
		}

	}
	destination->push_back(expression);     // If no colon at the end of the final expression it may be missed
	expression = "";
}




