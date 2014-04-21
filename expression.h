#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Number;
class Constant;
class Polynomial;

class Expression{
private:
	vector<Expression*> addition;
	vector<Expression*> multiplication;
	vector<Expression*> value;
	bool initialized;

public:
	Expression(Expression*);
	Expression(vector<Expression*>);
	Expression();

	virtual Expression* add(Expression* ex);
	virtual Expression* subtract(Expression* ex);

	virtual Expression* multiply(Expression* ex);
	virtual Expression* divide(Expression* ex);

	virtual Expression* exponentiate(Expression* ex);

	virtual bool canAdd(Expression* ex);
	virtual bool canSubtract(Expression* ex);

	virtual bool canMultiply(Expression* ex);
	virtual bool canDivide(Expression* ex);

	virtual bool canExponentiate(Expression* ex);

	virtual void negative();

	virtual void simplify();
	virtual void clear();
	virtual bool empty();

	virtual string toString();
	virtual double toDecimal();
	virtual string getName();

	virtual Expression* getValue1();
};

#endif
