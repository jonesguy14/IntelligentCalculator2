#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "expression.h"
#include "number.h"
#include "SumExVec.h"
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
	Expression* add(Expression* ex);
	Expression* subtract(Expression* ex);

	Expression* multiply(Expression* ex);
	Expression* divide(Expression* ex);

	Expression* exponentiate(Expression* ex);

	bool canAdd(Expression* ex);
	bool canSubtract(Expression* ex);

	bool canMultiply(Expression* ex);
	bool canDivide(Expression* ex);

	bool canExponentiate(Expression* ex);

	void negative();

	Expression* simplify();
	void clear();
	bool empty();

	string toString();
	double toDecimal();
	string getName();

	Expression* getValue1();
};

#endif
