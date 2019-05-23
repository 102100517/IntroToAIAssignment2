
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
		solve(*iter);
	}
	displayResults();
}



string BackwardsChaining::retrieveArguments(string arg, string expression)
{
	string result = arg; // Our result is the argument we're looking for + an operator and its antecedant

	for (string::size_type i = 0; i != string::npos; i)
	{
		string::size_type position = expression.find(arg, i);    // Find the position of the argument in the string
		i = position; // Move iterator to the argument we're currently on 
		char* txt = &expression[position];                       // current char we are checking against regex.
		regex operators("[<>=&~|]");                           //  String[int] not valid w/ regex


		while (regex_match(txt, operators))                  // Scroll back & append all the logical operator used
		{
			// If we get to the end of the string before a complete expression is created 
			// Then there is an error in the expression syntax
			if (position == 0)
			{
				break;
			}

			result.insert(result.begin(), expression[position]); // Unable to use insert with char

			// Get the next character in the string array
			position--;
			txt = &expression[position];
		}

		return result;
	}

	return result;
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


