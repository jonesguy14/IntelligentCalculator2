#include <iostream>
#include <exception>
#include <vector>

#include "binaryoperation.h"

using namespace std;

class shuntingStack{

private:
   vector<BinaryOperation> items;

public:
	shuntingStack(){

	}

	void push(BinaryOperation c){
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

	BinaryOperation getTop() {
        return items.back();
	}

	int isEmpty(){ return items.empty();}

	string toString(){
		string result	=	"";
		for(int i = 0; i < items.size(); i++){
			result	+= items[i].toString() + "\n";
		}
		return result;
	}
};
