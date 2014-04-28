/*
    Author: Achi Jones
*/
#include "SummationVector.h"

using namespace std;

SummationVector::SummationVector(Expression* e1, Expression* e2) {
    expression.push_back(e1);
    expression.push_back(e2);
}

SummationVector::SummationVector(vector<Expression*> e) {
    expression = e;
}

Expression* SummationVector::add(Expression* ex) {
    ex = ex->simplify();
    vector<Expression*> summer;
    if (expression.size() == 1) {
        if (expression[0]->getName() == "Adding Vector") {
            summer = expression[0]->getExpression();
        }
        else {
            return expression[0]->add(ex);
        }
    }
    else {
        summer = expression;
    }
    summer.push_back(ex);
    for (int i = 0; i < summer.size() - 1; i++) {
        if (SumTerms[i]->getName() != "Adding Vector") {
            Expression* temp = summer[i]->add(summer[summer.size() - 1]);
            if (temp->getName() != "Adding Vector") {
                summer[i] = temp;
                summer.erase(summer.end() - 1);
            }
        }
    }
    expression = summer;
    return this;
}

Expression* SumExVec::subtract(Expression* ex) {
    ex = ex->simplify();
    vector<Expression*> summer;
    if (expression.size() == 1) {
        if (expression[0]->getName() == "Adding Vector") {
            summer = expression[0]->getExpression();
        }
        else {
            return expression[0]->subtract(ex);
        }
    }
    else {
        summer = expression;
    }
    summer.push_back(ex);
    for (int i = 0; i < summer.size() - 1; i++) {
        if (SumTerms[i]->getName() != "Adding Vector") {
            Expression* temp = summer[i]->subtract(summer[summer.size() - 1]);
            if (temp->getName() != "Adding Vector") {
                summer[i] = temp;
                summer.erase(summer.end() - 1);
            }
        }
    }
    expression = summer;
    return this;
}

Expression* SummationVector::multiply(Expression* ex) {
    ex = ex->simplify();
    if (expression.size() == 1) {
        return expression[0]->multiply(ex);
    }
    if (ex->getName() == "Adding Vector") {
        vector<Expression*> oex = ex->getExpression();
        vector<Expression*> finalex;
        for (int i = 0; i < expression.size(); i++) {
            for (int j = 0; j < oex.size(); j++) {
                Expression* tmpe = expression[i]->multiply(oex[j]);
                finalex.push_back(tmpe);
            }
        }
        finalex = simplifyVec(finalex);
        SumExVec* finaladd = new SumExVec(finalex);
        return finaladd;
    }
    vector<Expression*> res_sum = expression;
    for (int i = 0; i < res_sum.size(); i++) {
        res_sum[i] = res_sum[i]->multiply(ex);
    }
    SumExVec* result = new SummationVector(res_sum);
    return result;
}

Expression* SummationVector::divide(Expression* ex) {
    vector<Expression*> res_sum = expression;
    for (int i = 0; i < res_sum.size(); i++) {
        res_sum[i] = res_sum[i]->divide(ex);
    }
    SumExVec* result = new SummationVector(res_sum);
    return result;
}

Expression* SummationVector::simplify() {
    expression = simplifyVec(expression);
    if (expression[0]->getName() == "Adding Vector") {
        vector<Expression*> tmpex = expression[0]->getExpression();
        if (tmpex.size() == 1 && tmpex[0]->getName() != "Adding Vector") {
            return tmpex[0];
        }
    }

    if (expression[0]->getName() == "Multiply Vector") {
        return expression[0]->simplify();
    } else {
        return expression[0];
    }
    return expression[0];
}

vector<Expression*> SummationVector::simplifyVec(vector<Expression*> vecex) {
    for (int i = 0; i < exvec.size(); i++) {
        exvec[i] = exvec[i]->simplify();
    }

    while (exvec.size() > 1) {
        exvec[0] = exvec[0]->add(exvec[1]);
        exvec.erase(exvec.begin() + 1);
    }

    return exvec;
}

string SummationVector::getName() {
    return "Adding Vector";
}

string SummationVector::toString() {
    string result = "";
    for (int i = 0; i < expression.size(); i++) {
        if (expression[i]->toDouble() != 0) {
            if (expression[i]->toDouble>=0) {
                result+="+";
                result+=expression[i]->toString();
            } else {
                result+=expression[i]->toString();
            }
        }
    }
    return result;
}

double SummationVector::toDecimal() {
    double n = 0;
    for (int i = 0; i < expression.size(); i++) {
        n += expression[i]->toDouble();
    }
    return n;
}

Expression* SummationVector::negative() {
    vector<Expression*> sumv;
    for (int i = 0; i < expression.size(); i++) {
        sumv.push_back(expression[i]->negative());
    }
    return sumv;
}

vector<Expression*> SummationVector::getExpression() {
    return expression;
}
