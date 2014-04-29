/*
    Author: Achi Jones
*/
#include "SumExVec.h"

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
            SummationVector* ex0 = static_cast<SummationVector*>(expression[0]);
            summer = ex0->getExpression();
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
        if (summer[i]->getName() != "Adding Vector") {
            Expression* temp = summer[i]->add(summer[summer.size() - 1]);
            if (temp->getName() != "Adding Vector") {
                summer[i] = temp;
                summer.erase(summer.end() - 1);
            }
        }
    }
    expression = summer;
    return this->simplify();
}

Expression* SummationVector::subtract(Expression* ex) {
    ex = ex->simplify();
    vector<Expression*> summer;
    if (expression.size() == 1) {
        if (expression[0]->getName() == "Adding Vector") {
            SummationVector* ex0 = static_cast<SummationVector*>(expression[0]);
            summer = ex0->getExpression();;
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
        if (summer[i]->getName() != "Adding Vector") {
            Expression* temp = summer[i]->subtract(summer[summer.size() - 1]);
            if (temp->getName() != "Adding Vector") {
                summer[i] = temp;
                summer.erase(summer.end() - 1);
            }
        }
    }
    expression = summer;
    return this->simplify();
}

Expression* SummationVector::multiply(Expression* ex) {
    ex = ex->simplify();
    if (expression.size() == 1) {
        return expression[0]->multiply(ex);
    }
    if (ex->getName() == "Adding Vector") {
        SummationVector* exs = static_cast<SummationVector*>(ex);
        vector<Expression*> oex = exs->getExpression();
        vector<Expression*> finalex;
        for (int i = 0; i < expression.size(); i++) {
            for (int j = 0; j < oex.size(); j++) {
                Expression* tmpe = expression[i]->multiply(oex[j]);
                finalex.push_back(tmpe);
            }
        }
        finalex = simplifyVec(finalex);
        SummationVector* finaladd = new SummationVector(finalex);
        return finaladd;
    }
    vector<Expression*> res_sum = expression;
    for (int i = 0; i < res_sum.size(); i++) {
        res_sum[i] = res_sum[i]->multiply(ex);
    }
    SummationVector* result = new SummationVector(res_sum);
    return result->simplify();
}

Expression* SummationVector::divide(Expression* ex) {
    vector<Expression*> res_sum = expression;
    for (int i = 0; i < res_sum.size(); i++) {
        res_sum[i] = res_sum[i]->divide(ex);
    }
    SummationVector* result = new SummationVector(res_sum);
    return result->simplify();
}

Expression* SummationVector::simplify() {
    expression = simplifyVec(expression);
    if (expression[0]->getName() == "Adding Vector") {
        SummationVector* ex0 = static_cast<SummationVector*>(expression[0]);
        vector<Expression*> tmpex = ex0->getExpression();
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

vector<Expression*> SummationVector::simplifyVec(vector<Expression*> exvec) {
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
        if (expression[i]->toDecimal() != 0) {
            if (expression[i]->toDecimal()>=0) {
                if (i!=0) {result+="+";}
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
        n += expression[i]->toDecimal();
    }
    return n;
}

Expression* SummationVector::negative() {
    vector<Expression*> sumv;
    for (int i = 0; i < expression.size(); i++) {
        sumv.push_back(expression[i]->negative());
    }
    SummationVector* negation = new SummationVector(sumv);
    return negation;
}

vector<Expression*> SummationVector::getExpression() {
    return expression;
}
