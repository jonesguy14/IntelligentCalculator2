#include <iostream>
#include <exception>
#include <vector>

#include "binaryoperation.h"

using namespace std;

class shuntingStack{

private:
   int MAX;
   int top;
   BinaryOperation* items;

public:
	shuntingStack(int sizey){
		MAX = sizey;
		top = -1;
		vector<BinaryOperation> items;
	}

	~shuntingStack(){ delete [] items; }

	void push(BinaryOperation c){
		if(isFull()){
			cout << "Stack Full!" << endl;
		}

		items[++top] = c;
	}

	BinaryOperation pop(){
		if(isEmpty()){
			throw "Error with input! Operator to term ratio does not match up.";
		}
        else {
            return items[top--];
        }
	}

	BinaryOperation getTop() {
        return items[top];
	}

	bool hasItems() {
        if (top>-1) {return true;}
        else return false;
	}

	int isEmpty(){ return top == -1; }

	int isFull(){ return top+1 == MAX; }

	string toString(){
		string result	=	"";
		for(int i = 0; i < top; i++){
			result	+= items[top].toString();
		}
		return result;
	}
};
