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

Expression* Constant::add(Expression* ex){
	if(ex->getName() == "Constant"){
        Constant* val		=	static_cast<Constant*>(ex);
		if(this->getType() == val->getType()){
			Constant* temp	=	new Constant(this->getType(), this->getCoeff()->add(val->getCoeff()));
			return temp;
		}else{
			SummationVector* sum = new SummationVector(this, ex);
			return sum;
		}
	}else{
		SummationVector* sum = new SummationVector(this, ex);
		return sum;
	}
}

Expression* Constant::subtract(Expression* ex){
	if(ex->getName() == "Constant"){
        Constant* val		=	static_cast<Constant*>(ex);
		if(this->getType() == val->getType()){
			Constant* temp	=	new Constant(this->getType(), this->getCoeff()->subtract(val->getCoeff()));
			return temp;
		}else{
			SummationVector* sum = new SummationVector(this, ex->negative());
			return sum;
		}
	}else{
		SummationVector* sum = new SummationVector(this, ex->negative());
		return sum;
	}
}

Expression* Constant::multiply(Expression* value){
	if(value->getName() == "Number"){
        Number* val		=	static_cast<Number*>(value);
        Constant* temp	=	new Constant(this->value, this->getCoeff()->multiply(val));
        return temp;
	}else{
		vector<Expression*> temp_vector;
		temp_vector.push_back(this);
		temp_vector.push_back(value);
		MultiplicationVector* temp	=	new MultiplicationVector(temp_vector);
		return temp;
	}
}

Expression* Constant::divide(Expression* value){
	if(value->getName() == "Number"){
        Number* val		=	static_cast<Number*>(value);
        MultiplicationVector* temp	=	new MultiplicationVector(this, val);
        return temp;
	}
	if(value->getName() == "Constant"){
        Constant* val		=	static_cast<Constant*>(value);
		if(this->getType() == val->getType()){
			MultiplicationVector* temp	=	new MultiplicationVector(this->getCoeff(), val->getCoeff());
			return temp;
		}
	}else{
		MultiplicationVector* temp	=	new MultiplicationVector(this, value);
		return temp;
	}
}

Expression* Constant::negative(){
    Constant* negation = new Constant(this->value, getCoeff()->negative());
    return negation;
}

Expression* Constant::simplify(){
	return this;
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
