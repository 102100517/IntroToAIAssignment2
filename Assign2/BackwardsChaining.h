#pragma once
#include "InferenceEngine.h"


class BackwardsChaining : public InferenceEngine
{
private:
	bool solve(string arg);
public:
	BackwardsChaining(ifstream &myFile);       // Constructor
	~BackwardsChaining();
	void execute();
};