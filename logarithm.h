#include "expression.h"

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Number;
class Constant;

class Logarithm : public Expression{
private:
	vector<Expression*> argument;
	vector<Expression*> base;

public:
	Logarithm(Expression*, Expression*);

	Expression* getBase();
	Expression* getArgument();

	Expression* add(Expression*);
	Expression* subtract(Expression*);
	Expression* multiply(Expression*);
	Expression* divide(Expression*);

	Expression* exponentiate(Expression*);

	bool canAdd(Expression*);
	bool canSubtract(Expression*);
	bool canDivide(Expression*);

	void negative();

	Expression* simplify();
	void clear();
	bool empty();

	string toString();
	double toDecimal();
	string getName();
};
