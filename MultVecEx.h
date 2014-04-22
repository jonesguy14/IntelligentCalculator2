#ifndef MultVecEx_H_
#define MultVecEx_H_
#include <iostream>
#include "expression.h"

class MultVecEx : public Expression {
private:
    vector<Expression*> numerator;
    vector<Expression*> denominator;
    
public:
    MultVecEx();
    MultVecEx(Expression* numerator, Expression* denominator);
    MultVecEx(vector<Expression*> numerator, vector<Expression*> denominator);
    MultVecEx(vector<Expression*> numerator);
    
    Expression* add(Expression* ex);
    //Expression* subtract(Expression* ex);
    Expression* multiply(Expression* ex);
    Expression* divide(Expression* ex);
    
    Expression* simplify();
    
    string toString();
    string getName();
    double toDecimal();
    
    vector<Expression*> simplifyVec();
    int GreatCommonFactor(int a, int b);
    
    vector<Expression*> getNumerator();
    vector<Expression*> getDenominator();
    
};
    
