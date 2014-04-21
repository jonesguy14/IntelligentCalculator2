#include "constant.h"

Constant::Constant(std::string value){
	this->value	=	value;
	Number* one	=	new Number(1);
	this->coefficient.push_back(one);
}

Expression* Constant::add(Expression* value){
	if(value->getName() == "Constant"){
		Expression* temp	=	value->getValue1();
		this->coefficient.push_back(this->coefficient.back()->add(temp));
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->add(value);
		return temp;
	}
}

Expression* Constant::subtract(Expression* value){
	if(value->getName() == "Constant"){
		Expression* temp	=	value->getValue1();
		this->coefficient.push_back(this->coefficient.back()->subtract(temp));
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->subtract(value);
		return temp;
	}
}

Expression* Constant::multiply(Expression* value){
	Expression* temp	=	new Expression(this);
	temp->multiply(value);
	return temp;
}

Expression* Constant::divide(Expression* value){
	Expression* temp	=	new Expression(this);
	temp->multiply(value);
	return temp;
}

Expression* Constant::exponentiate(Expression* value){
	Expression* temp	=	new Expression(this);
	temp->exponentiate(value);
	return temp;
}

bool Constant::canAdd(Expression* value){
	return (value->getName() == "Constant");
}

bool Constant::canSubtract(Expression* value){
	return (value->getName() == "Constant");
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

void Constant::negative(){
	this->coefficient.back()->negative();
}

void Constant::simplify(){
	// Do nothing
}
void Constant::clear(){
	this->coefficient.clear();
}
bool Constant::empty(){
	return (this->coefficient.empty());
}

std::string Constant::toString(){
	if(this->getValue1()->toDecimal() == 0){
		return "0";
	}
	if(this->getValue1()->toDecimal() == 1){
		return this->value;
	}
	return this->getValue1()->toString() + this->value;
}
double Constant::toDecimal(){
	double dec	=	0;
	if(this->value	==	"pi"){
		dec	=	3.1415926535;
	}else{
		dec	=	2.7182818284;
	}
	return this->getValue1()->toDecimal() * dec;
}
std::string Constant::getName(){
	return "Constant";
}

Expression* Constant::getValue1(){
	return this->coefficient.back();
}
