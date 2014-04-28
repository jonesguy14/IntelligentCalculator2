#ifndef EXPONENT_H_
#define EXPONENT_H_

#include "expression.h"
#include "number.h"
#include "MultVecEx.h"
#include "SumExVec.h"

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Number;
class Constant;
class Polynomial;

class Exponent : public Expression{
private:
	vector<Expression*> base;
	vector<Expression*> power;

public:
	Exponent(Expression*, Expression*);

	Expression* getBase();
	Expression* getPower();

	Expression* add(Expression*);
	Expression* subtract(Expression*);
	Expression* multiply(Expression*);
	Expression* divide(Expression*);


	bool canAdd(Expression*);
	bool canSubtract(Expression*);
	bool canMultiply(Expression*);
	bool canDivide(Expression*);

	Expression* negative();

	Expression* simplify();
	Expression* nthRoot(Exponent*);
	void clear();
	bool empty();

	string toString();
	double toDecimal();
	string getName();
};

#endif
