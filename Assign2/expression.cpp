#include "Expression.h"



expression::expression(argument* pArg)
{
	arg = pArg;
	left = NULL;
	right = NULL;
	parent = NULL;
	negated = false;
}


expression::~expression()
{
}

truthValue expression::getValue()
{
	if (negated)
	{
		if (arg->value == TRUE)
			return FALSE;
		else if (arg->value == FALSE)
			return TRUE;
		else
			return truthValue::UNKNOWN;
	}
	else
		return arg->value;
}

// getter for name
string expression::getName()
{
	return arg->name;
}

bool expression::setParent(expression* parentNode)
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

void expression::setAsNegated()
{
	negated = true;
}

bool expression::isOperator()
{
	return arg->isOperator();
}


