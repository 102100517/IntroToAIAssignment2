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
};

struct expression
{
	argument* arg; // Each argument exists independant of any one expression
	expression* left, *right;

	expression()
	{
		arg = NULL;
		left = NULL;
		right = NULL;
	}

	bool setParent(expression* parent)
	{
		if (parent->left == NULL)
		{
			parent->left = this;
			return true;
		}
		else if (parent->right == NULL)
		{
			parent->right = this;
			return true;
		}
		
		return false;
	}


};
