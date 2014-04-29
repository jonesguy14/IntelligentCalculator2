#include <iostream>
#include <stdio.h>

#include <vector>
#include "shuntingyard.h"

using namespace std;

int main(){
	try{

		ShuntingYard s1("2/5 + 3/5");
		cout << s1.getResult()->toString();
		/*ShuntingYard s2("(3 + 2*pi) * (3 - 2*pi)");
		cout << endl;
		ShuntingYard s3("2^(5/3 + pi) / (3rt:4)");
		cout << endl;
		ShuntingYard s4("2^(5/3 + pi) / ((3rt:4) * 2^pi*5)");
		cout << endl;
		ShuntingYard s5("((((log_5:((log_5:9 + 6 + 10) * 6))))) + 4 * 8 + e^(log_e:(5+6))/10 - sqrt:49 * 43rt:343 + pi * log_(log_55:5):(log_6:6)");
	*/}catch(const char* e){
		cout << e;
	}
}

