#include "number.h"

Number::Number(double value){
	this->value	=	value;
}

Expression* Number::add(Expression* value){
	if(value->getName() == "Number"){
		this->value	+=	value->toDecimal();
		return this;
	}else{
		Expression#include "number.h"

Number::Number(double value){
	this->value	=	value;
}

Expression* Number::add(Expression* value){
	if(value->getName() == "Number"){
		this->value	+=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->add(value);
		return temp;
	}
}

Expression* Number::subtract(Expression* value){
	if(value->getName() == "Number"){
		this->value	-=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->subtract(value);
		return temp;
	}
}

Expression* Number::multiply(Expression* value){
	if(value->getName() == "Number"){
		this->value	*=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->multiply(value);
		return temp;
	}
}

Expression* Number::divide(Expression* value){
	if(value->getName() == "Number" && this->toDecimal()/value->toDecimal() < .00001 && this->toDecimal()/value->toDecimal() > -.00001){
		this->value	/=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		Expression* temp2	=	temp->divide(value);
		return temp2;
	}
}

Expression* Number::exponentiate(Expression* value){
	if(value->getName() == "Number" && pow(this->toDecimal(), value->toDecimal()) < .00001 && pow(this->toDecimal(), value->toDecimal()) > -.00001){
		this->value	=	pow(this->toDecimal(), value->toDecimal());
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		Expression* temp2	=	temp->exponentiate(value);
		return temp2;
	}
}

bool Number::canAdd(Expression* value){
	return (value->getName() == "Number");
}

bool Number::canSubtract(Expression* value){
	return (value->getName() == "Number");
}

bool Number::canMultiply(Expression* value){
	return (value->getName() == "Number");
}

bool Number::canDivide(Expression* value){
	return (value->getName() == "Number" && this->toDecimal()/value->toDecimal() < .00001 && this->toDecimal()/value->toDecimal() > -.00001);
}

bool Number::canExponentiate(Expression* value){
	return (value->getName() == "Number" && pow(this->toDecimal(), value->toDecimal()) < .00001 && pow(this->toDecimal(), value->toDecimal()) > -.00001);
}

void Number::negative(){
	this->value *= -1.0;
}

Expression* Number::simplify(){
	return this;
}
void Number::clear(){
	this->value	=	0;
}
bool Number::empty(){
	return (this->value == 0);
}

string Number::toString(){
	ostringstream s;
	s << this->value;
	return s.str();
}
double Number::toDecimal(){
	return this->value;
}
string Number::getName(){
	return "Number";
}
* temp	=	new Expression(this);
		temp->add(value);
		return temp;
	}
}

Expression* Number::subtract(Expression* value){
	if(value->getName() == "Number"){
		this->value	-=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->subtract(value);
		return temp;
	}
}

Expression* Number::multiply(Expression* value){
	if(value->getName() == "Number"){
		this->value	*=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		temp->multiply(value);
		return temp;
	}
}

Expression* Number::divide(Expression* value){
	if(value->getName() == "Number" && this->toDecimal()/value->toDecimal() < .00001 && this->toDecimal()/value->toDecimal() > -.00001){
		this->value	/=	value->toDecimal();
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		Expression* temp2	=	temp->divide(value);
		return temp2;
	}
}

Expression* Number::exponentiate(Expression* value){
	if(value->getName() == "Number" && pow(this->toDecimal(), value->toDecimal()) < .00001 && pow(this->toDecimal(), value->toDecimal()) > -.00001){
		this->value	=	pow(this->toDecimal(), value->toDecimal());
		return this;
	}else{
		Expression* temp	=	new Expression(this);
		Expression* temp2	=	temp->exponentiate(value);
		return temp2;
	}
}

bool Number::canAdd(Expression* value){
	return (value->getName() == "Number");
}

bool Number::canSubtract(Expression* value){
	return (value->getName() == "Number");
}

bool Number::canMultiply(Expression* value){
	return (value->getName() == "Number");
}

bool Number::canDivide(Expression* value){
	return (value->getName() == "Number" && this->toDecimal()/value->toDecimal() < .00001 && this->toDecimal()/value->toDecimal() > -.00001);
}

bool Number::canExponentiate(Expression* value){
	return (value->getName() == "Number" && pow(this->toDecimal(), value->toDecimal()) < .00001 && pow(this->toDecimal(), value->toDecimal()) > -.00001);
}

void Number::negative(){
	this->value *= -1.0;
}

void Number::simplify(){
	// Do nothing
}
void Number::clear(){
	this->value	=	0;
}
bool Number::empty(){
	return (this->value == 0);
}

string Number::toString(){
	ostringstream s;
	s << this->value;
	return s.str();
}
double Number::toDecimal(){
	return this->value;
}
string Number::getName(){
	return "Number";
}
