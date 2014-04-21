#ifndef SHUNTINGYARD_H_INCLUDED
#define SHUNTINGYARD_H_INCLUDED

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdio.h>

#include "binaryoperation.h"
#include "shunting-stack.h"
#include "expression-stack.h"
#include "expression.h"
#include "logarithm.h"
#include "exponent.h"
#include "number.h"
#include "constant.h"

class Expression;
class Logarithm;
class Exponent;
class Number;
class Constant;
class shuntingStack;
class expressionStack;

class ShuntingYard{
private:
	std::string expression;
	std::vector<std::string> tokens;
	std::vector<BinaryOperation> operations;
	std::vector<Expression> expressions;
	void validate();
	void collapse();
	void identifyAll();
	void toRPN();
	std::string identify(std::string);
	Logarithm createLogarithm(BinaryOperation);
	Exponent createExponent(BinaryOperation);
	Number createNumber(BinaryOperation);
	Constant createConstant(BinaryOperation);
public:
	ShuntingYard(std::string);
	std::vector<BinaryOperation> getShuntingYard();
};

#endif // SHUNTINGYARD_H_INCLUDED
