#include "Expression.h"



expression::expression(argument* pArg)
{
	arg = pArg;
	left = NULL;
	right = NULL;
	parent = NULL;
	negated = pArg->isNegated();
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
	if (parentNode != NULL)
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

bool expression::antecedantIsOperator()
{
	if (parent->left - isOperator() || parent->left == this)
	{
		return true;
	}
	
	return false;
}

bool expression::consequentIsOperator()
{
	if (parent->right - isOperator() || parent->right == this)
	{
		return true;
	}
	return false;
}


argument* expression::getArg()
{
	return arg;
}


