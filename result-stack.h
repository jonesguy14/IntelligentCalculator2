#ifndef RESULT-STACK_H_INCLUDED
#define RESULT-STACK_H_INCLUDED

/*
	Written by James Steele
*/

#include <iostream>
#include <exception>
#include <vector>

#include "expression.h"

class Expression;

using namespace std;

class resultStack{

private:
   vector<Expression*> items;

public:
	resultStack(){

	}

	void push(Expression* c){
		items.push_back(c);
	}

	void pop(){
		if(isEmpty()){
			throw "Error with input! Operator to term ratio does not match up.";
		}
        else{
            items.pop_back();
        }
	}

	Expression* getTop() {
        return items.back();
	}

	int isEmpty(){ return items.empty();}

	string toString(){
		string result	=	"";
		for(int i = 0; i < items.size(); i++){
			result	+= items[i]->toString() + "\n";
		}
		return result;
	}
};


#endif // RESULT-STACK_H_INCLUDED
