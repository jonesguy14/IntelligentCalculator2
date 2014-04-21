#include <iostream>
#include <stdio.h>
#include <vector>
#include "shuntingyard.h"

using namespace std;

int main(){
	vector<Expression*> expressions;

	Number n1(2145.451);
	Number n2(2145.451);
	Constant pi("pi");
	Constant pi2("pi");

	expressions.push_back(pi.multiply(&pi2));

	expressions.push_back(expressions[0]->subtract(&n2));
	expressions.push_back(expressions[1]->add(&n2));
	expressions.push_back(expressions[2]->multiply(&pi));
	cout << expressions.back()->toString() << endl;

	/*
	try{
		//ShuntingYard s1("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
		//cout << endl;
		//ShuntingYard s2("((((log_5:((log_5:9 + 6 + 10) * 6))))) + 4 * 8 + e^(log_e:(5+6))/10 - sqrt:49 * 43rt:343 + pi * log_(log_55:5):(log_6:6)");
	}catch(const char* e){
		cout << e;
	}
	*/
}
