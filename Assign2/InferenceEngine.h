#pragma once
#include <regex>
#include <string>
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

enum booleanOperation
{
	AND, OR, XAND, XOR, NOT
};

struct expression
{
	string name;
	bool truthValue = false;
	expression* antecedent;
	expression* consequent;
};
/*
struct expression : antecedent
{
	expression* antecendent;
	booleanOperation operation;
};
*/

class InferenceEngine
{
private:
	ifstream* textFile;
	void readInFile();
	
protected:
	list <string> expressions;   // Contains expressions to evaluate e.g: (A v B) => C
	list <string> knownFacts;   // Contains a list of arguments known to be true
	list <string> goals;       // Holds aguments to find the truth value of
	list <string> findInExpression(string arg);
	void displayResults();
public:
	InferenceEngine(ifstream &myFile);
	~InferenceEngine();
	virtual void execute();
};
