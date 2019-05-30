# IntroToAIAssignment2
The is is the second group assignment for the unit CS30019: Introduction to Artificial Intelligence

##Authors:
Thomas Wright - 101470604
James Hassal - 


## Features & Bugs
### Data representation
The expressions read in via the knowledge base are stored as a binary tree.
In this manner the expresion (A & B) || C is represented as:
	
       ||
     /    \
    &      C
  /   \
 A     B

Each argument in the expression has a pointer to each of its children & its parent.
Using these the algorithm is able to determine antecedants/consequents relative to the
expression it is currently evaluating. 

These objects have some getter/setter methods, however these are mostly for convienience so that 
expression->argument->name can instead be written as expression->getName()
Most of the underlying variables are still publicly accessible.


### Algorithms Implemented

Currently this assignment has forwards chaining & backwards chaining implemented. 
These both use the same underlying algorithm to infer the results, however they still operate as two 
distinct algorithms as each searches a different side of the binary tree expressions.
