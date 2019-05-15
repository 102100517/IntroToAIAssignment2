#pragma once
#include "InferenceEngine.h"
using namespace std;

class BackwardsChaining : public InferenceEngine
{
private:
	
public:
	BackwardsChaining(fstream &myFile);       // Constructor
	~BackwardsChaining();
};