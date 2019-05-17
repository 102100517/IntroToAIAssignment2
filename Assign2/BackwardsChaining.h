#pragma once
#include "InferenceEngine.h"


class BackwardsChaining : public InferenceEngine
{
private:
	
public:
	BackwardsChaining(ifstream &myFile);       // Constructor
	~BackwardsChaining();
};