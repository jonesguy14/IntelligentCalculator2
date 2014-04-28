/*
	Written by James Steele
*/

#include "binaryoperation.h"

BinaryOperation::BinaryOperation(std::string operation, std::string type){
	this->binary_operation	=	operation;
	this->binary_type		=	type;
}

BinaryOperation::BinaryOperation(std::string operation, std::string left, std::string right, std::string type){
	this->binary_operation	=	operation;
	this->binary_left		=	left;
	this->binary_right		=	right;
	this->binary_type		=	type;
}

std::string BinaryOperation::getBinaryLeft(){
	return this->binary_left;
}
std::string BinaryOperation::getBinaryRight(){
	return this->binary_right;
}
std::string BinaryOperation::getBinaryOperation(){
	return this->binary_operation;
}
std::string BinaryOperation::getBinaryType(){
	return this->binary_type;
}

std::string BinaryOperation::toString(){
	return this->binary_operation + "(" + this->binary_left + ", " + this->binary_right + ")";
}
