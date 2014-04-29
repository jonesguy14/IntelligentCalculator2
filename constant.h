#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "expression.h"
#include "number.h"
#include "SumVecEx.h"
#include "MultVecEx.h"

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Number;
class Constant;
class Polynomial;

class Constant : public Expression{
private:
	std::string value;
	vector<Expression*> coefficient;

public:
	Constant(std::string);
	Constant(std::string, Expression*);

	Expression* add(Expression* ex);
	Expression* subtract(Expression* ex);

	Expression* multiply(Expression* ex);
	Expression* divide(Expression* ex);

	Expression* negative();

	Expression* simplify();

	std::string toString();
	double toDecimal();
	std::string getName();

	std::string getType();

	Expression* getCoeff();
};

#endif
