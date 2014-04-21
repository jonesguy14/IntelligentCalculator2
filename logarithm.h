#include "expression.h"

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Number;
class Constant;
class Polynomial;

class Logarithm : public Expression{
private:
	vector<Expression*> argument;
	vector<Expression*> base;

public:
	Logarithm(Expression, Expression);
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

	void simplify();
	void clear();
	bool empty();

	string toString();
	double toDecimal();
	string getName();
};
