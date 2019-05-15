#pragma once
#include <list>
#include <fstream>
using namespace std;

struct consequent
{
	string name;
	bool truthValue;
};

struct antecedent : consequent
{
	consequent* rConsequent;
};


class InferenceEngine
{
private:
	fstream* textFile;
	void readInFile();
public:
	
	InferenceEngine(fstream &myFile);
	~InferenceEngine();
};
