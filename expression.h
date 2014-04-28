#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Expression {
private:
    vector<Expression*> expression;
    vector<Expression*> numerator;
    vector<Expression*> denominator;
    char sign;

public:
    virtual Expression* add(Expression* ex) = 0;
    virtual Expression* subtract(Expression* ex) = 0;
    virtual Expression* multiply(Expression* ex) = 0;
    virtual Expression* divide(Expression* ex) = 0;

    virtual Expression* simplify() = 0;

    void negative();
    char getSign();

    virtual string toString() = 0;
    virtual double toDecimal() = 0;
    virtual string getName() = 0;

};

#endif
