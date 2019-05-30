#pragma once
#include "InferenceEngine.h"
class ForwardsChaining :
	public InferenceEngine
{
private:
	truthValue solve(argument* arg);
public:
	ForwardsChaining(string path);
	~ForwardsChaining();
	void execute();
};

