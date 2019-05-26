
#include "BackwardsChaining.h"

BackwardsChaining::BackwardsChaining(ifstream &aFile): InferenceEngine(aFile)
{
	
}

BackwardsChaining::~BackwardsChaining()
{
}

// Entry point for chaining algorithm. Allows for solving multiple arguments
void BackwardsChaining::execute()
{
	for (auto iter = goals.begin(); iter != goals.end() ; iter++)
	{
		
	}

}




bool BackwardsChaining::solve(string arg)
{
	// FOR EACH EXPRESSION

	/* CASE
	 (arg & q)
	 (arg || q) 
		return false

	(arg => q)
		knownFacts.push_back(q)

	(q => arg)
		if (solve(q))
			return true
	
	*/
	return false;
}


