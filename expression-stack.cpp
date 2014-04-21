#include <iostream>
#include <vector>

#include "binaryoperation.h"

using namespace std;

class expressionStack {

private:
   int top;
   vector<string> items;

public:
	expressionStack(){
		top = -1;
	}

	~expressionStack(){}

	void push(string expression){
		items.push_back(expression);
		top++;
	}

	string pop(){
		if (isEmpty()){
			throw "Expression stack is empty";
		}
        else {
			string result	=	items.at(top);
			top--;
			items.pop_back();
            return result;
        }
	}

	void post_pop() {
        items.pop_back();
	}

	string getTop() {
        return items.at(top);
	}

	bool hasItems() {
        if (top>-1) {return true;}
        else return false;
	}

	int isEmpty(){ return top == -1; }
};
