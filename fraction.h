#include "expression.h"

class Expression;
class Fraction;
class Logarithm;
class Exponent;
class Number;
class Constant;
class Polynomial;

class Fraction : public Expression{
private:
	vector<Expression> numerator;
	vector<Expression> denominator;

public:
	Fraction(Expression, Expression);
	Expression add(Expression ex);
	Expression subtract(Expression ex);
	Expression multiply(Expression ex);
	Expression divide(Expression ex);
	Expression exponentiate(Expression ex);

	Expression simplify();

	string toString();
	double toDecimal();
	string getName();
}
