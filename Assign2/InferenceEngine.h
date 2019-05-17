#pragma once
#include <list>
#include <fstream>
using namespace std;

enum booleanOperation
{
	AND, OR, XAND, XOR, NOT
};

struct consequent
{
	string name;
	bool truthValue;
};

struct antecedent : consequent
{
	consequent* rConsequent;
};

struct expression : antecedent
{
	expression* antecendent;
	booleanOperation operation;
};


class InferenceEngine
{
private:
	ifstream* textFile;
	void readInFile();
	//string readExpression();
	list <string> goals;
	list <string> facts;
public:
	
	InferenceEngine(ifstream &myFile);
	~InferenceEngine();
};
