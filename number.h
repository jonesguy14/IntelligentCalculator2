/*
	Written by James Steele
*/

#ifndef NUMBER_H_
#define NUMBER_H_

#include "expression.h"

#include <cmath>
#include <sstream>

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Constant;
class MultiplicationVector;
class SummationVector;

class Number : public Expression{
private:
	double value;

public:
	Number(double);

	Expression* add(Expression* ex);
	Expression* subtract(Expression* ex);

	Expression* multiply(Expression* ex);
	Expression* divide(Expression* ex);

	Expression* negative();
	Expression* simplify();

	string toString();
	double toDecimal();
	string getName();
};
#endif
