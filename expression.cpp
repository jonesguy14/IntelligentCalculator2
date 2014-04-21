#include "expression.h"

Expression::Expression(Expression* exp){
	this->value.push_back(exp);
}

Expression::Expression(vector<Expression*> value){
	this->addition	=	value;
}

Expression::Expression(){
	// Do nothing
}

Expression* Expression::add(Expression* value){
	if(!this->value.empty()){
		this->addition.push_back(this->value.back());
		this->addition.push_back(value);
		this->value.clear();
	}else{
		this->addition.push_back(value);
	}
	return this;
}

Expression* Expression::subtract(Expression* value){
	if(!this->value.empty()){
		value->negative();
		this->addition.push_back(this->value.back());
		this->addition.push_back(value);
		this->value.clear();
	}else{
		value->negative();
		this->addition.push_back(value);
	}
	return this;
}

Expression* Expression::multiply(Expression* value){
	if(this->value.empty()){
		if(!this->addition.empty()){
			Expression* temp	=	new Expression(this->addition);
			this->multiplication.push_back(temp);
			this->addition.clear();
		}
		this->multiplication.push_back(value);
	}else{
		Expression* temp	=	this->value.back();
		this->multiplication.push_back(temp);
		this->multiplication.push_back(value);
		this->value.clear();
	}
	return this;
}

Expression* Expression::divide(Expression* value){
	/*
		Waiting on Fraction to be implemented
	*/

	//Fraction temp(this, value);
	//return temp;
}

Expression* Expression::exponentiate(Expression* value){
	/*
		Waiting on Exponent to be implemented
	*/
	//Exponent temp(this, value);
	//return temp;
}

void Expression::negative(){
	if(!this->multiplication.empty()){
		this->multiplication.back()->negative();
	}else{
		unsigned int length	=	this->addition.size();
		for(unsigned int i = 0; i < length; i++){
			this->addition[i]->negative();
		}
	}
}

void Expression::simplify(){
	unsigned int length	=	this->addition.size();
	for(unsigned int i = 0; i < length; i++){
		if(this->addition[i]->empty()){
			continue;
		}
		for(unsigned int j = 0; j < length; j++){
			if(this->addition[i]->canAdd(this->addition[j]) && !this->addition[j]->empty()){
				this->addition[i]->add(this->addition[j]);
				this->addition[j]->clear();
			}
		}
	}


	length	=	this->multiplication.size();

	if(this->addition.size() == 1 && length > 1){
		Expression temp(this->addition);
		this->multiplication.push_back(&temp);
		length++;
	}

	for(unsigned int i = 0; i < length; i++){
		if(this->multiplication[i]->empty()){
			continue;
		}
		for(unsigned int j = 0; j < length; j++){
			if(this->multiplication[i]->canMultiply(this->multiplication[j]) && !this->multiplication[j]->empty()){
				this->multiplication[i]->multiply(this->multiplication[j]);
				this->multiplication[j]->clear();
			}
		}
	}

	length	=	this->multiplication.size();
	vector<Expression*> temp;

	for(unsigned int i = 0; i < length; i++){
		if(!this->multiplication[i]->empty()){
			temp.push_back(this->multiplication[i]);
		}
	}

	this->multiplication	=	temp;

	length	=	this->addition.size();

	for(unsigned int i = 0; i < length; i++){
		if(!this->addition[i]->empty()){
			temp.push_back(this->addition[i]);
		}
	}

	this->addition	=	temp;
}

void Expression::clear(){
	this->addition.clear();
	this->multiplication.clear();
	this->value.clear();
}

bool Expression::empty(){
	return (this->addition.empty() && this->multiplication.empty() && this->value.empty());
}

string Expression::toString(){
	string result		=	"";

	unsigned int length	=	this->multiplication.size();

	for(unsigned int i = 0; i < length; i++){
			if(i > 0){
				result += " * ";
			}
			result	+=	"(" + this->multiplication[i]->toString() + ")";
	}

	length	=	this->addition.size();

	for(unsigned int i = 0; i < length; i++){
			if(!this->multiplication.empty()){
				if(this->addition[i]->toDecimal() > 0){
					result += " + ";
				}else{
					result += " - ";
					this->addition[i]->negative();
				}
			}
			result	+=	this->addition[i]->toString();
	}

	return result;
}

double Expression::toDecimal(){
	unsigned int length	=	this->addition.size();

	double result		=	0;

	for(unsigned int i = 0; i < length; i++){
			result	+=	this->addition[i]->toDecimal();
	}

	length	=	this->multiplication.size();

	for(unsigned int i = 0; i < length; i++){
		result	*=	this->multiplication[i]->toDecimal();
	}

	return result;
}

string Expression::getName(){
	return "Expression";
}

bool Expression::canAdd(Expression* value){
	return false;
}
bool Expression::canSubtract(Expression* value){
	return false;
}
bool Expression::canMultiply(Expression* value){
	return false;
}
bool Expression::canDivide(Expression* value){
	return false;
}
bool Expression::canExponentiate(Expression* value){
	return false;
}

Expression* Expression::getValue1(){
	if(!this->value.empty()){
		return this->value.back();
	}
	if(this->value.empty() && this->addition.empty()){
		return this->multiplication.back();
	}
	if(this->value.empty() && !this->addition.empty()){
		return this->addition.back();
	}
}
