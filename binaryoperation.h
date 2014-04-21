#ifndef ABSTRACT_H_INCLUDED
#define ABSTRACT_H_INCLUDED

#include <iostream>
#include <vector>

class BinaryOperation{
private:
	std::string binary_operation;
	std::string binary_left;
	std::string binary_right;
	std::string binary_type;
public:
	BinaryOperation(std::string, std::string);
	BinaryOperation(std::string, std::string, std::string, std::string);
	std::string getBinaryLeft();
	std::string getBinaryRight();
	std::string getBinaryOperation();
	std::string getBinaryType();
	std::string toString();
};

#endif // ABSTRACT_H_INCLUDED
