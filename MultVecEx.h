#ifndef MULTVECEX_H_INCLUDED
#define MULTVECEX_H_INCLUDED

#include <iostream>
#include "expression.h"
#include "number.h"
#include "SumExVec.h"

class MultiplicationVector : public Expression {
private:
    vector<Expression*> numerator;
    vector<Expression*> denominator;

public:
    MultiplicationVector();
    MultiplicationVector(Expression* numerator, Expression* denominator);
    MultiplicationVector(vector<Expression*> numerator, vector<Expression*> denominator);
    MultiplicationVector(vector<Expression*> numerator);

    Expression* add(Expression* ex);
    Expression* subtract(Expression* ex);
    Expression* multiply(Expression* ex);
    Expression* divide(Expression* ex);

    Expression* simplify();

    string toString();
    string getName();
    double toDecimal();

    Expression* negative();

    vector<Expression*> simplifyVec(vector<Expression*>);
    int GreatCommonFactor(int a, int b);

    vector<Expression*> getNumerator();
    vector<Expression*> getDenominator();

};

#endif // MULTVECEX_H_INCLUDED
