#pragma once
#include "argument.h"
#include "enums.h"
#include <string>
 
using namespace std;
// Each variable exists as an independant node whose value
// is updated as expressions are created & evaluated
// Replaces a simple boolean as an unknown state is required

class expression
{
public:
	//constructor with pointers to the arguments
	expression(argument* arg);
	//destructor
	~expression();
	//returns the value
	truthValue getValue();
	//return the name of the arugment
	string getName();
	//set parent node with a pointer
	bool setParent(expression* parentNode);
	//mark as negated
	void setAsNegated();
	//asks if the current expression is an operator
	bool isOperator();
	//Check if the value before is an operator
	bool antecedantIsOperator();
	//check if the value after is an operator
	bool consequentIsOperator();
	//return the argument
	argument* getArg();
	
	argument * arg; // Each argument exists independant of any one expression
	//set the left argument, right and parent of the current arg
	expression * left, *right, *parent;

private:
	bool negated;
	truthValue value;


};