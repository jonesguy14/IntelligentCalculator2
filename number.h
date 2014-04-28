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
class Polynomial;

class Number : public Expression{
private:
	double value;

public:
	Number(double);

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
};
#endif
