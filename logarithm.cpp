#include "logarithm.h"
#include <cmath>
#include <vector>


Logarithm::Logarithm(Expression* base, Expression* argument){
	this->base.push_back(base);
	this->argument.push_back(argument);
}

Expression* Logarithm::getBase(){
	return this->base.back();
}
Expression* Logarithm::getArgument(){
	return this->argument.back();
}

Expression* Logarithm::add(Expression* addend){
	if(canAdd(addend)){
		Logarithm* exLog = static_cast<Logarithm*>(addend);
		bool sameBase = exLog->getBase()->toDecimal() == this->getBase()->toDecimal();
		bool sameArg = exLog->getArgument()->toDecimal() == this->getArgument()->toDecimal();
		if(sameBase && sameArg){
			Number* two = new Number(2);
			vector<Expression*> exVec;
			exVec.push_back(two);
			exVec.push_back(addend);
			MultiplicationVector* retEx = new MultiplicationVector(exVec);
			return retEx;
		}
		else if(sameBase && !sameArg){
			vector<Expression*> exVec;
			exVec.push_back(getArgument());
			exVec.push_back(exLog->getArgument());
			MultiplicationVector* newArg = new MultiplicationVector(exVec);
			Logarithm* retLog = new Logarithm(getBase(),newArg);
			return retLog;
		}
	}
	SummationVector* retEx = new SummationVector(this, addend);
	return retEx;
}

bool Logarithm::canAdd(Expression* ex){
	if(ex->getName() == "Logarithm"){
	Logarithm* exLog = static_cast<Logarithm*>(ex);
	bool sameBase = exLog->getBase()->toDecimal() == this->getBase()->toDecimal();
	bool sameArg = exLog->getArgument()->toDecimal() == this->getArgument()->toDecimal();
		if(sameBase)
			return true;
		return false;
	}
	return false;
}

Expression* Logarithm::subtract(Expression* subtrahend){
	if(this->toDecimal() == subtrahend->toDecimal()){
		Number* zero = new Number(0);
		return zero;
	}
	if(canSubtract(subtrahend)){
		Logarithm* exLog = static_cast<Logarithm*>(subtrahend);
		bool sameBase = exLog->getBase()->toDecimal() == this->getBase()->toDecimal();
		bool sameArg = exLog->getArgument()->toDecimal() == this->getArgument()->toDecimal();
		if(sameBase && sameArg){
			Number* zero = new Number(0);
			return zero;
		}
		else if(sameBase && !sameArg){
			MultiplicationVector* newArg = new MultiplicationVector(getArgument(),exLog->getArgument());
			Logarithm* retLog = new Logarithm(getBase(),newArg);
			return retLog;
		}
	}
	subtrahend->negative();
	SummationVector* retEx = new SummationVector(this, subtrahend);
	return retEx;
}

bool Logarithm::canSubtract(Expression* ex){
	if(ex->getName() == "Logarithm"){
	Logarithm* exLog = static_cast<Logarithm*>(ex);
	bool sameBase = exLog->getBase()->toDecimal() == this->getBase()->toDecimal();
	bool sameArg = exLog->getArgument()->toDecimal() == this->getArgument()->toDecimal();
		if(sameBase)
			return true;
		return false;
	}
	return false;
}

Expression* Logarithm::multiply(Expression* multiplicand){
	std::vector<Expression*> exVec;
	exVec.push_back(this);
	exVec.push_back(multiplicand);
	MultiplicationVector* retEx = new MultiplicationVector(exVec);
	return retEx;
}

Expression* Logarithm::divide(Expression* dividend){
	if(canDivide(dividend)){
		Number* retNum = new Number(this->toDecimal()/dividend->toDecimal());
		return retNum;
	}
	Logarithm* exLog = static_cast<Logarithm*>(dividend);
	bool sameBase = exLog->getBase()->toDecimal() == this->getBase()->toDecimal();
	bool sameArg = exLog->getArgument()->toDecimal() == this->getArgument()->toDecimal();
		if(sameBase && sameArg){
			Number* one = new Number(1);
			return one;
		}
	MultiplicationVector* retEx = new MultiplicationVector(this, dividend);
	return retEx;
}

bool Logarithm::canDivide(Expression* ex){
	if(ex->getName() == "Logarithm"){
		if((this->toDecimal()/ex->toDecimal()) == floor(this->toDecimal()/ex->toDecimal())){
			return true;
		}
		return false;
	}
}

Expression* Logarithm::negative(){
	Number* neg1 = new Number(-1);
	vector<Expression*> negVec;
	negVec.push_back(neg1);
	negVec.push_back(this);
	MultiplicationVector* negEx = new MultiplicationVector(negVec);
	return negEx;
}
Expression* Logarithm::simplify(){
	if(getArgument()->toDecimal() == 0){
		throw "Logarithm: log(0); undefined";
	}
	if(getBase()->toDecimal() == 1){
		throw "Logarithm: log_1:x; undefined";
	}
	if((getBase()->toDecimal() <= 0) || (getArgument()->toDecimal() <= 0)){
		throw "Logarithm: negative base and/or argument; non-real result";
	}
	if(getArgument()->toDecimal() == 1){
		Number* zero = new Number(0);
		return zero;
	}
	if(getArgument()->toDecimal() == getBase()->toDecimal()){
		Number* one = new Number(1);
		return one;
	}
	if(getArgument()->getName() == "Exponent"){
		vector<Expression*> simpLogVec;
		Exponent* arg = static_cast<Exponent*>(getArgument());

		if(getBase() == arg->getBase()){
			return arg->getPower();
		}

		simpLogVec.push_back(arg->getPower());

		Logarithm* newLog = new Logarithm(getBase(),arg->getBase());
		simpLogVec.push_back(newLog);

		MultiplicationVector* simpLog = new MultiplicationVector(simpLogVec);
		return simpLog;
	}
	if(log10(getArgument()->toDecimal())/log10(getBase()->toDecimal()) == floor(log10(getArgument()->toDecimal())/log10(getBase()->toDecimal()))){
		Number* evalLog = new Number(log10(getArgument()->toDecimal())/log10(getBase()->toDecimal()));
		return evalLog;
	}
		return this;
}

std::string Logarithm::toString(){
	std::ostringstream ss;
	ss<< "log_" << getBase()->toString() << ":(" << getArgument()->toString() << ")";
	return ss.str();
}

double Logarithm::toDecimal(){
	double log	=	log10(this->getArgument()->toDecimal())/log10(this->getBase()->toDecimal());
	return log;
}


std::string Logarithm::getName(){
	return "Logarithm";
}
