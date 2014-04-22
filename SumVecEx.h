#ifndef SumVecEx_H_
#define SumVecEx_H_
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
    //Expression* subtract(Expression* ex);
    Expression* multiply(Expression* ex);
    Expression* divide(Expression* ex);
    
    Expression* simplify();
    
    string toString();
    string getName();
    double toDecimal();
    
    vector<Expression*> simplifyVec();    
    vector<Expression*> getExpression();
    
};
    
