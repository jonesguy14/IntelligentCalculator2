#include "constant.h"

Constant::Constant(std::string value){
	this->value	=	value;
	Number* one	=	new Number(1);
	this->coefficient.push_back(one);
}

Constant::Constant(std::string value, Expression* coeff) {
    this->value = value;
    this->coefficient.push_back(coeff);
}

Expression* Constant::add(Expression* value){
	if(value->getName() == "Constant"){
        Constant* valc = static_cast<Constant*>(value);
        Expression* temp	=	valc->getCoeff();
		this->coefficient.push_back(this->coefficient.back()->add(temp));
		return this;
	}else{
		SummationVector* sum = new SummationVector(this, value);
		return sum;
	}
}

Expression* Constant::subtract(Expression* ex){
	if(ex->getName() == "Constant"){
        Constant* valc = static_cast<Constant*>(ex);
		Expression* temp	=	valc->getCoeff();
		this->coefficient.push_back(this->coefficient.back()->subtract(temp));
		return this;
	}else{
		SummationVector* sum = new SummationVector(this, ex->negative());
		return sum;
	}
}

Expression* Constant::multiply(Expression* value){
    Number* one = new Number(1);
	MultiplicationVector* multy = new MultiplicationVector(this, one);
	Expression* ex = multy->multiply(value);
	return ex;
}

Expression* Constant::divide(Expression* value){
	Number* one = new Number(1);
	MultiplicationVector* multy = new MultiplicationVector(this, one);
	Expression* ex = multy->divide(value);
	return ex;
}

bool Constant::canAdd(Expression* ex){
    if (ex->getName() == "Constant") {
        Constant* exc = static_cast<Constant*>(ex);
        if (exc->getType()==this->value) {return true;}
        else {return false;}
    }
	else {return false;}
}

bool Constant::canSubtract(Expression* ex){
	if (ex->getName() == "Constant") {
        Constant* exc = static_cast<Constant*>(ex);
        if (exc->getType()==this->value) {return true;}
        else {return false;}
    }
	else {return false;}
}

bool Constant::canMultiply(Expression* value){
	return false;
}

bool Constant::canDivide(Expression* value){
	return false;
}

bool Constant::canExponentiate(Expression* value){
	return false;
}

Expression* Constant::negative(){
    Expression* newco = getCoeff()->negative();
    Constant* negation = new Constant(value, newco);
    return negation;
}

Expression* Constant::simplify(){
	return this;
}
void Constant::clear(){
	this->coefficient.clear();
}
bool Constant::empty(){
	return (this->coefficient.empty());
}

std::string Constant::toString(){
	if(this->getCoeff()->toDecimal() == 0){
		return "0";
	}
	if(this->getCoeff()->toDecimal() == 1){
		return this->value;
	}
	return this->getCoeff()->toString() + this->value;
}
double Constant::toDecimal(){
	double dec	=	0;
	if(this->value	==	"pi"){
		dec	=	3.1415926535;
	}else{
		dec	=	2.7182818284;
	}
	return this->getCoeff()->toDecimal() * dec;
}
std::string Constant::getName(){
	return "Constant";
}

Expression* Constant::getCoeff(){
	return this->coefficient.back();
}

std::string Constant::getType() {
    return this->value;
}
