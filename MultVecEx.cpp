#include "MultVecEx.h"

using namespace std;

MultVecEx::MultVecEx() {}

MultVecEx::MultVecEx(Expression* numerator, Expression* denominator) {
    this->numerator.push_back(numerator);
    this->denominator.push_back(denominator);
}

MultVecEx::MultVecEx(vector<Expression*> numerator, vector<Expression*> denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

MultVecEx::MultVecEx(vector<Expression*> numerator) {
    this->numerator = numerator;
}

Expression* MultVecEx::add(Expression* ex) {
    if (numerator.size() == 1) {
        if (numerator[0]->getName() == "Multiplication Vector") {
            //Expression* element = MultVecEx(numerator[0]);
            MultVecEx* nummy = static_cast<MultExVec*>(numerator[0]);
            numerator = nummy->getNumerator();
        }
        else if (denominator.size() == 0) {
            return numerator[0]->add(ex);
        }
    }

    if (ex->getName() == "Adding Vector") {
        return ex->add(this);
    }

    if (ex->getName() == "Multiplication Vector") {
        vector<Expression*> ex_num = ex->getNumerator();
        vector<Expression*> ex_den = ex->getDenoinator();

        if (numerator.size()==1 && denominator.size()==1 && ex_num.size()==1 && ex_den.size()==1) {
            if (numerator[0]->getName()=="Integer" && denominator[0]->getName()=="Integer" && ex_num[0]->getName()=="Integer" && ex_den[0]->getName()=="Integer") {
                //if its a fraction with integers, simplify the fraction
                int num_int = (int)(numerator[0]->toDecimal() * ex_den[0]->toDecimal() + ex_num[0]->toDecimal() * denominator[0]->toDecimal());
                int den_int = (int)(denominator[0]->toDecimal() * ex_den[0]->toDecimal());
                int gcf_int = GreatCommonFactor(num_int, den_int);
                num_int /= gcf_int;
                den_int /= gcf_int;
                Expression* new_num(new Number(num_int));
                Expression* new_den(new Number(den_int));
                MultVecEx* result = MultVecEx(new_num, new_den);
                return result;
                }
            }

        //see if other MultVecEx has same denominator
        double den_val = 0;
        for (int i = 0; i < denominator.size(); i++) {
            den_val *= denominator[i]->toDecimal();
        }
        double ex_den_val = 0;
        for (int j = 0; j < ex_den.size(); j++) {
            ex_den_val *= ex_den[j]->toDecimal();
        }
        if (abs(ex_den_val - den_val) < 0.000001) { //same denominator
            if (numerator.size() == 1 && ex_num.size() == 1) {
                numerator[0] = numerator[0]->add(ex_num[0]);
                return this;
            }

            vector<Expression*> result_vec;

            for (int i = 0; i < numerator.size(); i++) {
                for (int j = 0; j < ex_num.size(); j++) {
                    if (numerator[0]->toDecimal() != 0 && ex_num[0]->toDecimal() != 0) {
                        Expression* tryDivide = numerator[i]->divide(ex_num[j]);
                        if (tryDivide->getName()!="Multiply Vector" && tryDivide->getName()!="Adding Vector") {
                            result_vec.push_back(ex_num[j]);
                            Number* one_int = new Number(1);
                            ex_num[j] = one_int;
                            numerator[i] = tryDivide;
                        }
                        else {
                            Expression* otherDivide = ex_num[j]->divide(numerator[i]);
                            if (otherDivide->getName()!="Multiply Vector" && otherDivide->getName()!="Adding Vector") {
                                result_vec.push_back(numerator[i]);
                                Number* one_int = new Number(1);
                                numerator[i] = one_int;
                                ex_num[j] = otherDivide;
                                }
                            }
                        }
                    }
                }

            if (result_vec.size() == 0) {
                vector<Expression*> summer;
                summer.push_back(this);
                summer.push_back(ex);
                SumExVec* result = new SumExVec(summer);
                return result;
            }
            ex_num    = simplifyVec(ex_num);
            numerator = simplifyVec(numerator);
            vector<Expression*> summer;
            summer.push_back(ex_num[0]);
            summer.push_back(numerator[0]);
            double int_test = summer[0]->toDecimal() + summer[1]->toDecimal();
            if (int_test == round(int_test)) {
                Number* comb_int = Number((int)round(int_test));
                result_vec.push_back(comb_int);
            } else {
                SumExVec* sum_final = new SumExVec(summer);
                result_vec.push_back(sum_final);
            }

            MultExVec* final_mult = new MultVecEx(result_vec, denominator);
            return final_mult;
        }
    }

    if (ex->getName()!="Integer" && ex->getName()!="Adding Vector" && ex->getName()!="Multiplication Vector") {
        for (int i = 0; i < numerator.size(); i++) {
            if (abs(numerator[i]->toDecimal() - ex->toDecimal()) < 0.0001) {
                if (numerator.size() == 2) {
                    if (numerator[0]->getName() == "Integer") {
                        Number* int_one = new Number(1);
                        numerator[0] = numerator[0]->add(int_one);
                        }
                    else if (numerator[1]->getName() == "Integer") {
                        Number* int_one = new Number(1);
                        numerator[1] = numerator[1]->add(int_one);
                        }
                    return this;
                }

                vector<Expression*> new_mult_ex;
                vector<Expression*> new_sum_ex;
                for (int n = 0; n < numerator.size(); n++) {
                    if (j != i) {
                        new_sum_ex.push_back(numerator[n]);
                    }
                Number* int_one = new Number(1);
                new_sum_ex.push_back(int_one);
                SumExVec* sumf = new SumExVec(new_sum_ex);
                new_mult_ex.push_back(sumf);
                new_mult_ex.push_back(ex);
                MultVecEx* mult_final = MultVecEx(mult_vec_ex);
                return mult_final;
            }
        }
    }

    if (numerator.size() == 1 && denominator.size() == 1 && ex->getName() == "Integer") {
        if (numerator[0]->getName() == "Integer" && denominator[0]->getName() == "Integer") {
            return ex->add(this);
        }
    }

    vector<Expression*> sumv;
    sumv.push_back(this);
    sumv.push_back(ex);
    SumVecEx* sum_fin = new SumVecEx(sumv);
    return sum_fin;
}

Expression* MultVecEx::multiply(Expression* ex) {
    if (ex->getName() == "Adding Vector") {
        return ex->multiply(this);
    }

    if (ex->getName() == "Integer" && denominator.size() == 1 && numerator.size() == 1) {
        if (denominator[0]->getName() == "Integer" && numerator[0]->getName() == "Integer") {
            numerator.push_back(ex);
            return this->simplify();
        }
    }

    if (ex->getName() == "Multiply Vector") {
        ex_num = ex->getNumerator();
        ex_den = ex->getDenominator();
        for (int i = 0; i < numerator.size(); i++) {
            ex_num.push_back(numerator[i]);
        }
        for (int i = 0; i < denominator.size(); i++) {
            ex_den.push_back(denominator[i]);
        }
        ex_num = simplifyVec(ex_num);
        ex_den = sumplifyVec(ex_den);
        MultVecEx* mult_fin = new MultVecEx(ex_num, ex_den);
        return mult_fin;
    }

    for (int i = 0; i < denominator.size(); i++) {
        if (denominator[i]->toDecimal == ex->toDecimal()) {
            denominator.erase(denominator.begin() + i);
            return this;
        }
    }

    vector<Expression*> multys = numerator;
    multys.push_back(ex->simplify());
    for (int i = 0; i < multys.size() - 1; i++) {
        if (multys[i]->getName() == multys[multys.size() - 1]->getName()) {
            if (multys[i]->getName() != "Multiply Vector") {
                Expression* e = multys[i]->multiply(multys[multys.size() - 1]);
                if (e->getName() != "Multiply Vector") {
                    multys[i] = e;
                    multys.erase(multys.end()- 1);
                }
            }
        }
    }
    MultVecEx* final_mult = new MultVecEx(multys, denominator);
    return final_mult;
}

Expression* MultVecEx::divide(Expression* ex) {
    vector<Expression*> multys = denominator;
    multys.push_back(ex->simplify());
    for (int i = 0; i < numerator.size(); i++) {
        if (numerator[i]->toDecimal() == ex->toDecimal()) {
            numerator.erase(numerator.begin() + i);
            return this;
        }
    }
    for (int i = 0; i < numerator.size(); i++) {
        Expression* e;
        e = numerator[i]->divide(ex);
        e = e.simplify();
        if (e->getName() != "Multiply Vector") {
            numerator[i] = e;
            return this;
        }

        Expression* e2;
        e2 = ex->divide(numerator[i]);
        e2 = e2->simplify();
        if (e2->getName() != "Multiply Vector") {
            if (numerator.size() > 1) {
                numerator.erase(numerator.begin() + 1);
            }
            else {
                Number* one_int = new Number(1);
                numerator[i] = one_int;
            }

            denominator.push_back(e2);
            return this;
        }

        if (e->getName() == "Multiply Vector") {
            vector<Expression*> onum = e->getNumerator();
            vector<Expression*> oden = e->getDenominator();
            if (onum.size() > 0 && oden.size() > 0) {
                if (onum[0]->getName() == "Integer" && oden[0]->getName() == "Integer") {
                    numerator[i] = onum[0];
                    multys[multys.size() - 1] = oden[0];
                }
            }
        }
    }

    Expression* e;
    for (int i = 0; i < multys.size(); i++) {
        if (multys[i]->getName() == multys[multys.size() - 1]->getName()) {
            if (multys[i]->getName() != "Multiply Vector") {
                e = multys[i]->divide(multys[multys.size() - 1]);
                if (e->getName() != "Multiply Vector") {
                    multys[i] = e;
                    multys.erase(multys.end() - 1);
                }
            }
        }
    }

    MultVecEx final_mult = new MultVecEx(numerator, multys);
    return final_mult;
}

vector<Expression*> MultVecEx::getNumerator() {
    return numerator;
}
vector<Expression*> MultVecEx::getDenominator() {
    return denominator;
}

string MultVecEx::getName() {
    return "Multiply Vector";
}

Expression* simplify() {
    if (denominator.size() > 0) {
        for (int i = 0; i < denominator.size(); i++) {
            if (denominator[i]->toDouble() == 0) {
                throw "Tried to divide by zero.";
            }
        }
    }
    if (toDecimal() == round(toDecimal())) {
        Number* reduced = new Number(round(toDouble()));
        return reduced;
    }
    numerator = simplifyVec(numerator);
    denominator = simplifyVec(denominator);
    if (denominator.size() == 1) {
        if (denominator[0]->getName() == "Multiply Vector") {
            MultVecEx* red = new MultVecEx(denominator[0]);
            denominator = red->getNumerator();
            vector<Expression*> rednum = red->getNumerator();
            for (int i = 0; i < rednum.size(); i++) {
                numerator.push_back(rednum[i]);
            }
        }
    }

    if (numerator[0]->getName() == "Multiply Vector") {
        MultVecEx* mu = new MultVecEx(numerator[0]);
        numerator = mu->getNumerator();
        vector<Expression*> temp_den = mu->getDenominator();
        for (int i = 0; i < temp_den.size(); i++) {
            denominator.push_back(temp_den[i]);
        }
    }

    if (denominator.size() != 0) {
        if (denominator.size()!=1 && denominator[0]->getName()!="Multiply Vector") {
            Expression* e = numerator[0]->divide(denominator[0]);
            if (e->getName() != "Multiply Vector") {
                numerator[0] = e;
                denominator.erase(denominator.begin());
            } else {
                MultVecEx multmp = new MultVecEx(e);
                vector<Expression*> tnum = multmp->getNumerator();
                vector<Expression*> tden = multmp->getDenominator();
                numerator = tnum;
                denominator = tden;
            }
        }
    }

    if (numerator.size() == 1 || denominator.size() == 1) {
        if (numerator.size() == 0) {
            return denominator[0];
        }
        if (denominator.size() == 0) {
            return numerator[0];
        }
    }

    return this;
}

vector<Expression*> MultVecEx::simplifyVec(vector<Expression*> exvec) {
    for (int i = 0; i < exvec.size(); i++) {
        exvec[i] = exvec[i]->simplify();
    }

    while (exvec.size()>1) {
        exvec[0] = exvec[0]->multiply(exvec[1]);
        vec.erase(vec.begin() + 1);
    }

    return exvec;
}

int MultVecEx::GreatCommonFactor(int a, int b) {
    int abs = abs(a-b);
    for (int n = 2; n <= abs; n++) {
        if (a%n == 0 && b%n == 0) {
            return i * GreatCommonFactor(a/i, y/i);
        }
    }
    return 1;
}

double MultVecEx::toDecimal() {
    double result = 1;
    for (int i = 0; i < numerator.size(); i++) {
        result *= numerator[i]->toDecimal();
    }
    for (int j = 0; j < denominator.size(); j++) {
        result /= denominator[j]->toDecimal();
    }
    return result;
}

string MultVecEx::toString() {
    string result = "";
    for (int i = 0; i < numerator.size(); i++) {
        result += numerator[i]->toString();
        if (i<numerator.size()-1) {
            result += "*";
        }
    }
    for (int i = 0; i < denominator.size(); i++) {
        result += "/";
        result += denominator[i]->toString();
    }
    return result;
}

void MultVecEx::negative() {
    expression[0]->negative();
}
