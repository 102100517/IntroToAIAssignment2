#pragma once
#include "InferenceEngine.h"


class BackwardsChaining : public InferenceEngine
{
private:
	truthValue solve(argument* arg);
public:
	BackwardsChaining(string path);       // Constructor
	~BackwardsChaining();
	void execute();
};