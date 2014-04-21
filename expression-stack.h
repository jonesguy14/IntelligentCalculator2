#include <iostream>
#include <vector>

#include "binaryoperation.h"

using namespace std;

class expressionStack {

private:
   vector<string> items;

public:
	expressionStack(){

	}


	void push(string expression){
		items.push_back(expression);
	}

	string pop(){
		if (isEmpty()){
			cout << "Empty" << endl;
			throw "Expression stack is empty";
		}
        else {
			string result	=	items.back();
			items.pop_back();
            return result;
        }
	}

	string getTop() {
		if(!items.empty()){
        	return items.back();
		}else{
			return "";
		}
	}

	bool isEmpty(){ return items.empty();}

	string toString(){
		string result	=	"";
		for(int i = 0; i < items.size(); i++){
			result	+= items[i];
		}
		return result;
	}
};
