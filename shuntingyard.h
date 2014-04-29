/*
	Written by James Steele
*/

#ifndef SHUNTINGYARD_H_INCLUDED
#define SHUNTINGYARD_H_INCLUDED

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "binaryoperation.h"
#include "shunting-stack.h"
#include "expression-stack.h"
#include "result-stack.h"
#include "number.h"

class shuntingStack;
class expressionStack;

class ShuntingYard{
private:
	std::string expression;
	std::vector<std::string> tokens;
	std::vector<BinaryOperation> operations;
	shuntingStack shunting_yard_stack;
	shuntingStack ordered_shunting_yard_stack;
	resultStack result_stack;
	expressionStack expression_stack;

	void validate();
	void collapse();
	std::string identify(std::string);
	void identifyAll();
	void toRPN(); // To Reverse Polish Notation
	void toPN(); // To Polish Notation
	void postFix();

	void add(BinaryOperation);
	void subtract(BinaryOperation);
	void multiply(BinaryOperation);
	void divide(BinaryOperation);
	void exponentiate(BinaryOperation);

public:
	ShuntingYard(std::string);
	std::vector<BinaryOperation> getShuntingYard();
	Expression* getResult();
};

#endif // SHUNTINGYARD_H_INCLUDED
