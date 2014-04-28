#ifndef SUMEXVEC_H_INCLUDED
#define SUMEXVEC_H_INCLUDED
#include <iostream>
#include "expression.h"

class SumVecEx : public Expression {
private:
    vector<Expression*> expression;

public:
    SumVecEx();
    SumVecEx(Expression* e1, Expression* e2);
    SumVecEx(vector<Expression*> e);

    Expression* add(Expression* ex);
    Expression* subtract(Expression* ex);
    Expression* multiply(Expression* ex);
    Expression* divide(Expression* ex);

    Expression* simplify();

    string toString();
    string getName();
    double toDecimal();

    Expression* negative();

    vector<Expression*> simplifyVec();
    vector<Expression*> getExpression();

};


#endif // SUMEXVEC_H_INCLUDED
