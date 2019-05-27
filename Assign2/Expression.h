#pragma once
#include <string>

using namespace std;
// Each variable exists as an independant node whose value
// is updated as expressions are created & evaluated
// Replaces a simple boolean as an unknown state is required
enum truthValue
{
	FALSE, TRUE, UKNOWN
};

struct argument
{
	string name;
	truthValue value;

	argument(string pName, truthValue pValue)
	{
		name = pName;
		value = pValue;
	}
};

struct expression
{
	argument* arg; // Each argument exists independant of any one expression
	expression* left, *right, *parent;

	expression()
	{
		arg = NULL;
		left = NULL;
		right = NULL; 
		parent = NULL;
	}

	bool setParent(expression* parentNode)
	{
		if (parentNode->left == NULL)
		{
			parentNode->left = this;
			parent = parentNode;
			return true;
		}
		else if (parentNode->right == NULL)
		{
			parentNode->right = this;
			parent = parentNode;
			return true;
		}
		
		return false;
	}


};
