#pragma once
#include "InferenceEngine.h"


class BackwardsChaining : public InferenceEngine
{
private:
	//Recursive function the will return the true values based on an argument given
	truthValue solve(argument* arg);
public:
	BackwardsChaining(string path);       // Constructor
	//destructor
	~BackwardsChaining();
	//Entry point for solve so that it can solve and return multiple truth values
	void execute();
};