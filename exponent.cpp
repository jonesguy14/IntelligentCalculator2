#include "Exponent.h"
#include <stdio.h>

Exponent::Exponent(Expression* base, Expression* power){
    this->sign = '+';
	this->base.push_back(base);
	this->power.push_back(power);
}

Expression* Exponent::getBase(){
	return this->base.back();
}

Expression* Exponent::getPower(){
	return this->power.back();
}

Expression* Exponent::add(Expression* addend){
	if(canAdd(addend)){
		Number* two = new Number(2);
		vector<Expression*> ex;
		ex.push_back(two);
		ex.push_back(addend);
		MultVecEx* retEx = new MultVecEx(ex);
		return retEx;
	}
	SumVecEx* retEx = new SumVecEx(this, addend);
	return retEx;
}

bool Exponent::canAdd(Expression* ex){
	if(ex->getName() == "Exponent"){
        Exponent* exm = static_cast<Exponent*>(ex);
		bool sameBase = exm->getBase()->toDecimal() == this->getBase()->toDecimal();
		bool samePow  = exm->getPower()->toDecimal() == this->getPower()->toDecimal();
		if(sameBase && samePow){
			return true;
		}
		return false;
	}
	return false;

}

Expression* Exponent::subtract(Expression* subtrahend){
	if(this->toDecimal() == subtrahend->toDecimal()){
		Number* zero = new Number(0);
		return zero;
	}
	subtrahend->negative();
	SumVecEx* retEx = new SumVecEx(this, subtrahend);
	return retEx;

}

bool Exponent::canSubtract(Expression* ex){
	if(ex->getName() == "Exponent"){
        Exponent* exs = static_cast<Exponent*>(ex);
		bool sameBase = exs->getBase()->toDecimal() == this->getBase()->toDecimal();
		bool samePow  = exs->getPower()->toDecimal() == this->getPower()->toDecimal();
		if(sameBase && samePow){
			return true;
		}
	}
	else
		return false;
}

Expression* Exponent::multiply(Expression* multiplicand){
	if(canMultiply(multiplicand)){
        Exponent* exm = static_cast<Exponent*>(multiplicand);
		SumVecEx* sumPows = new SumVecEx(this->getPower(),exm->getPower());
		Exponent* retEx = new Exponent(this->getBase(),sumPows);
		return retEx;
	}
	vector<Expression*> ex;
	ex.push_back(this);
	ex.push_back(multiplicand);
	MultVecEx* retEx = new MultVecEx(ex);
	return retEx;
}

bool Exponent::canMultiply(Expression* ex){
	if(ex->getName() == "Exponent"){
		Exponent* exm = static_cast<Exponent*>(ex);
		bool sameBase = (exm->getBase()->toDecimal() == this->getBase()->toDecimal());
		if(sameBase){
			return true;
		}
	}
	return false;
}

Expression* Exponent::divide(Expression* dividend){
	if(canDivide(dividend)){
        Exponent* exd = static_cast<Exponent*>(dividend);
        exd->getPower()->negative();
		SumVecEx* subtractPows = new SumVecEx(this->getPower(),exd->getPower());
		Exponent* retEx = new Exponent(this->getBase(),subtractPows);
		return retEx;
	}
	MultVecEx* retEx = new MultVecEx(this,dividend);
	return retEx;

}

bool Exponent::canDivide(Expression* ex){
	if(ex->getName() == "Exponent"){
        Exponent* exd = static_cast<Exponent*>(ex);
		bool sameBase = (exd->getBase()->toDecimal() == this->getBase()->toDecimal());
		if(sameBase){
			return true;
		}
	}
	return false;
}

Expression* Exponent::negative(){
	if (sign=='+') {sign = '-';}
	else {sign = '+';}
	return this;
}

char Exponent::getSign() {
    return sign;
}

Expression* Exponent::simplify(){
	if((getPower()->toDecimal()) == 0 || (getBase()->toDecimal() == 1)){
		Number* one = new Number(1);
		return one;
	}
	if(getPower()->toDecimal() == 1){
		return getBase();
	}
	if(getBase()->toDecimal() == 0){
		Number* zero = new Number(0);
		return zero;
	}
	if((getBase()->toDecimal() == 0) && (getPower()->toDecimal() == 0)){
		throw "Exponent Class: Entire expression is undefined";
	}
	if(abs(pow(getBase()->toDecimal(),getPower()->toDecimal()) - floor(pow(getBase()->toDecimal(),getPower()->toDecimal()))) <= .001){
		Number* evalExponent = new Number(pow(getBase()->toDecimal(),getPower()->toDecimal()));
		return evalExponent;
	}
	//Evaluate a fraction power if possible (including nth roots):
	if((this->base.size() == 1) && (getBase()->getName() == "Number") && (getPower()->getName() == "MultVecEx")) {
		MultVecEx* powm = static_cast<MultVecEx*>(getPower());
		vector<Expression*> den;
		den = powm->getDenominator();
		vector<Expression*> num;
		num = powm->getNumerator();
		if(den.size() == 1 && den.at(0)->getName() == "Number" && num.size() == 1 && num.at(0)->getName() == "Number"){//check if the power is a Number fraction

		// The following code will try and simplify the fraction exponent through prime factorization of the exponents' base

			Number* numerator = new Number(num.at(0)->toDecimal());
			Number* denominator = new Number(den.at(0)->toDecimal());

			if(numerator->toDecimal() != 1){//check if the fraction is not an nth root
				Exponent* newExp = new Exponent(this->getBase(),numerator);
				Number* evalExp = new Number(newExp->simplify()->toDecimal());
				Number* one = new Number(1);

				MultVecEx* nrt = new MultVecEx(one,denominator);
				Exponent* nrtExp = new Exponent(evalExp,nrt);

				return nthRoot(nrtExp);
			}

			return nthRoot(this);
		}
	}
	return this;
}

Expression* Exponent::nthRoot(Exponent* exp){//Must pass in an Exponent with Number base and MultVecEx Fraction power with Number(1) numerator and Number denominator.

    	bool baseIsNeg = false;
    Exponent* eexp = static_cast<Exponent*>(exp);
    MultVecEx* multe = static_cast<MultVecEx*>(eexp->getPower());
	int nrt = (multe->getDenominator()).at(0)->toDecimal();
        int base = eexp->getBase()->toDecimal();
        if(base < 0){
          	baseIsNeg = true;
        	base *=-1;
  		}

    	int powCount = 0;
        int coeff = 1;
        int newBase = base;
        int primeNums = 1;

    		// powCount counts the # of 2s that divide newBase
    		while (newBase%2 == 0){
      			newBase /= 2;
        		powCount++;
        		if(powCount == nrt){
            			coeff *= 2;
            			powCount = 0;
        		}
    		}

            	if(powCount != 0 ){
                	for(int j = 0; j<powCount; ++j){
                                primeNums *= 2;
                            }
			    powCount = 0;
            		}

		// n must be odd at this point.  So we can skip one element (Note i = i +2)
    		for (int i = 3; i <= sqrt(newBase); i = i+2){
         		// While i divides n, increase powCount
         		while (newBase%i == 0){
               			newBase /= i;
               			powCount++;
               			if(powCount == nrt){
                     			coeff *=i;
                     			powCount = 0;
                   		}
         		}

			if(powCount != 0 ){
                            for(int j = 0; j<powCount; ++j){
                                primeNums *= i;
                            }
			    powCount = 0;
            		}

    		}


            newBase *= primeNums;

            if(coeff == 1){
                if(baseIsNeg){
                    newBase *= -1;
                }
		Number* baseEx = new Number(newBase);
		Exponent* retExp = new Exponent(baseEx,eexp->getPower());
		return retExp;
	    }
            if(newBase == 1){
                if(baseIsNeg){
                    coeff *= -1;
                }
		Number* retEx = new Number(coeff);
		return retEx;
            }
            if(baseIsNeg){
                coeff *= -1;
            }

 	    Number* retNum = new Number(coeff);
 	    Number* basenum = new Number(newBase);
	    Exponent* retExp = new Exponent(basenum, eexp->getPower());
	    vector<Expression*> vec;
	    vec.push_back(retNum);
	    vec.push_back(retExp);
	    MultVecEx* retEx = new MultVecEx(vec);

	    return retEx;

}

double Exponent::toDecimal(){
	double exponentVal = pow(this->getBase()->toDecimal(),this->getPower()->toDecimal());
	return exponentVal;

}

void Exponent::clear(){
	this->base.clear();
	this->power.clear();
}
bool Exponent::empty(){
	return (this->base.empty() && this->power.empty());
}

std::string Exponent::toString(){
	return this->getBase()->toString() + "^(" + this->getPower()->toString() + ")";
}

std::string Exponent::getName(){
	return "Exponent";
}
