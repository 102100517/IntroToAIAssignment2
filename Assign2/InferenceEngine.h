#pragma once

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
	
	list <string> expressions;    // Contains expressions to evaluate e.g: (A v B) => C
	list <string> knownFacts;   // Contains a list of arguments known to be true
protected:
	string getAntecedant(string arg);
	string getContainingArgument(string arg);
public:
	InferenceEngine(ifstream &myFile);
	~InferenceEngine();
};
