/*
	Written by James Steele
*/

#include "number.h"

Number::Number(double value){
	this->value	=	value;
}

Expression* Number::add(Expression* value){
	if(value->getName() == "Number"){
		this->value	+=	value->toDecimal();
		return this;
	}else{
		SummationVector* temp	=	new SummationVector(this, value);
		return temp;
	}
}

Expression* Number::subtract(Expression* value){
	if(value->getName() == "Number"){
		this->value	-=	value->toDecimal();
		return this;
	}else{
		SummationVector* temp	=	new SummationVector(this, value->negative());
		return temp;
	}
}

Expression* Number::multiply(Expression* value){
	if(value->getName() == "Number"){
		this->value	*=	value->toDecimal();
		return this;
	}else{
		std::vector<Expression*> temp_mult_vector;
		temp_mult_vector.push_back(this);
		temp_mult_vector.push_back(value);
		MultiplicationVector* temp	=	new MultiplicationVector(temp_mult_vector);
		return temp;
	}
}

Expression* Number::divide(Expression* value){
	if(value->getName() == "Number" && this->toDecimal()/value->toDecimal() < .00001 && this->toDecimal()/value->toDecimal() > -.00001){
		this->value	/=	value->toDecimal();
		return this;
	}else{
		MultiplicationVector* temp	=	new MultiplicationVector(this, value);
		return temp2;
	}
}

Expression* Number::negative(){
	Number temp	=	new Number(this->value * -1.0);
	return temp;
}

Expression* Number::simplify(){
	return this;
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
