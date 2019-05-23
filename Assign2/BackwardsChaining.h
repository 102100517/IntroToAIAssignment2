#pragma once
#include "InferenceEngine.h"


class BackwardsChaining : public InferenceEngine
{
private:
	string retrieveArguments(string arg, string expression);
	bool solve(string arg);
public:
	BackwardsChaining(ifstream &myFile);       // Constructor
	~BackwardsChaining();
	void execute();
};