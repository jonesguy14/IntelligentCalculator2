/*
	Written by James Steele
*/

#include "shuntingyard.h"

void printVector(std::vector<std::string>);
void printVector(std::vector<BinaryOperation>);
int countLParens(std::string);
int countRParens(std::string);
int countLogs(std::string);
void trimParens(std::string*);
bool isNumber(std::string);

ShuntingYard::ShuntingYard(std::string expression){
	this->expression	=	expression;
	this->validate();
	this->identifyAll();
	this->toRPN();
	this->toPN();
	this->postFix();
	//printVector(this->operations);
}

void ShuntingYard::validate(){
	unsigned int lparen	=	0;
	unsigned int rparen	=	0;

	unsigned int length	=	this->expression.size();

	std::string current_expression = "";
	std::vector<std::string> tokens;

	if(length < 1){
		throw "Please input an expression";
	}

	for(unsigned int i = 0; i < length; i++){
		switch(this->expression[i]){
			case '(':
				current_expression += this->expression[i];
				lparen++;
				break;
			case ')':
				current_expression += this->expression[i];
				rparen++;
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':

			case ':':
			case '_':
			case 'l':
			case 'o':
			case 'g':

			case 'r':
			case 't':
			case 'q':

			case 'p':
			case 'i':

			case 'e':

			case 'a':
			case 'n':
			case 's':

			case '.':
				current_expression += this->expression[i];
				break;

			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				tokens.push_back(current_expression);
				tokens.push_back(std::string(1, this->expression[i]));
				current_expression = "";
				break;
			case ' ':
				break;
			default:
				throw "Invalid character";
		}
	}
	if(current_expression != ""){
		tokens.push_back(current_expression);
	}
	if(lparen > rparen){
		throw "Too many left parentheses";
	}
	if(rparen > lparen){
		throw "Too many right parentheses";
	}
	this->tokens	=	tokens;
	this->collapse();
}

void ShuntingYard::collapse(){
	int p	=	0;
	for(std::vector<std::string>::iterator i = this->tokens.begin(); i != this->tokens.end(); ++i){
		if(i->find("(") < i->size()){
			if(p < 0){
				p	=	0;
			}
			p	+=	countLParens(*i);
			continue;
		}
		if(p > 0 && (i - this->tokens.begin()) > 1){
			/*
				If we still have open parens, add the previous two items to our current one and then replace them with an
				empty string.
			*/
			if(*(i-2) != "+" && *(i-2) != "-" && *(i-2) != "*" && *(i-2) != "/" && *(i-2) != "^"){
				*i		=	*(i-2) + *(i-1) + *i;
				*(i-2)	=	"";
				*(i-1)	=	"";
			}else{
				*i		=	*(i-1) + *i;
				*(i-1)	=	"";
			}
			p		-=	countRParens(*i);
		}
	}

	/*
		The previous operation left blank spaces, so let's take some time to remove them
		While we're at it, let's trim the parentheses
	*/
	std::vector<std::string> temp;

	for(std::vector<std::string>::iterator i = this->tokens.begin(); i != this->tokens.end(); ++i){
		if(*i != ""){
			trimParens(&(*i));
			temp.push_back(*i);
		}
	}

	this->tokens	=	temp;
}

void ShuntingYard::identifyAll(){
	for(std::vector<std::string>::iterator i = this->tokens.begin(); i != this->tokens.end(); ++i){
		std::string id		=	this->identify(std::string(*i));
		std::string left	=	"";
		std::string right	=	"";


		if(id == "Logarithm"){
			unsigned int logs	=	countLogs(*i);
			unsigned int c		=	0;
			unsigned int length	=	i->length();
			unsigned int pos	=	0;

			for(unsigned int j = 4; j < length; j++){
				if((*i)[j] == '('){
					c++;
				}
				else if((*i)[j] == ')'){
					c--;
				}else if(j > 0 && c <= 0){
					pos	=	j;
					break;
				}
			}
			if(pos > 4){
				left	=	i->substr(0, pos);
				left	=	left.substr(4);
				trimParens(&left);
			}else{
				pos		=	i->find(":");
				left	=	i->substr(0, pos);
				left	=	left.substr(4);
			}
			right	=	i->substr(pos+1);
			BinaryOperation binary("Logarithm", left, right, "Logarithm");
			this->operations.push_back(binary);
		}
		if(id == "Square root"){
			unsigned int pos	=	0;

			right	=	"1/2";
			pos		=	i->find(":");
			left	=	i->substr(pos);
			left	=	left.substr(1);

			BinaryOperation binary("Exponent", left, right, "Exponent");
			this->operations.push_back(binary);
		}
		if(id == "Nth root"){
			unsigned int pos	=	0;
			unsigned int pos2	=	0;
			pos2		=	i->find("rt:");
			right		=	i->substr(0, pos2);
			right		=	"1/" + right;
			pos			=	i->find(":");
			left		=	i->substr(pos);
			left		=	left.substr(1);

			BinaryOperation binary("Exponent", left, right, "Exponent");
			this->operations.push_back(binary);
		}
		if(id == "Expression"){
			BinaryOperation binary(*i, "Expression");
			this->operations.push_back(binary);
		}
		if(id == "Operator"){
			BinaryOperation binary(*i, "Operator");
			this->operations.push_back(binary);
		}
		if(id == "Constant"){
			BinaryOperation binary(*i, "Constant");
			this->operations.push_back(binary);
		}
		if(id == "Number"){
			BinaryOperation binary(*i, "Number");
			this->operations.push_back(binary);
		}
	}
}

std::string ShuntingYard::identify(std::string id){
	switch(id[0]){
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
				return "Operator";
			break;
		case 'e':
			if(!id[1]){
				return "Constant";
			}else{
				throw "Invalid input: unexpected token found after euler's number";
			}
			break;
		case 'p':
			if((!id[2] || id[2] == ')') && id[1] == 'i'){
				return "Constant";
			}else{
				throw "Invalid input: unexpected token found after pi";
			}
			break;
		case 'l':
			if(id.find("log_") < id.size()){
				return "Logarithm";
			}
			break;
		default:
			if(isNumber(id)){
				return "Number";
			}else if(id.find("rt:") < id.size() && !(id.find("sqrt:") < id.size())){
				return "Nth root";
			}else if(id.find("sqrt:") < id.size()){
				return "Square root";
			}else{
				return "Expression";
			}
			break;
	}
}

void ShuntingYard::toRPN(){
	/*
		This method takes our operation vector and transforms it into a Reverse Polish Notation vector,
		which we'll use to evaluate our input
	*/

	/*
		Precedence
		I could use a struct or a basic class for this, but it's easier to just use a primitive
	*/
	unsigned int addition		=	2;
	unsigned int subtraction	=	2;
	unsigned int multiplication	=	3;
	unsigned int division		=	3;
	unsigned int exponentiation	=	4;

	unsigned int current		=	0;
	unsigned int next			=	0;

	/*
		We need to iterate through our operation vector
	*/
	for(std::vector<BinaryOperation>::iterator i = this->operations.begin(); i != this->operations.end(); ++i){
		if(i->getBinaryType() == "Operator"){
			/*
				Set our priorities
			*/
			if(this->expression_stack.getTop() == "+"){
				current	=	addition;
			}
			if(this->expression_stack.getTop() == "-"){
				current	=	subtraction;
			}
			if(this->expression_stack.getTop() == "*"){
				current	=	multiplication;
			}
			if(this->expression_stack.getTop() == "/"){
				current	=	division;
			}
			if(this->expression_stack.getTop() == "^"){
				current	=	exponentiation;
			}

			if(i->getBinaryOperation() == "+"){
				next	=	addition;
			}
			if(i->getBinaryOperation() == "-"){
				next	=	subtraction;
			}
			if(i->getBinaryOperation() == "*"){
				next	=	multiplication;
			}
			if(i->getBinaryOperation() == "/"){
				next	=	division;
			}
			if(i->getBinaryOperation() == "^"){
				next	=	exponentiation;
			}

			if(next > current){
				this->expression_stack.push(i->getBinaryOperation());
			}
			if(next <= current){
				BinaryOperation temp(this->expression_stack.getTop(), "Operation");
				this->shunting_yard_stack.push(temp);
				this->expression_stack.pop();
				this->expression_stack.push(i->getBinaryOperation());
			}
		}else{
			this->shunting_yard_stack.push(*i);
		}
	}
	while(!expression_stack.isEmpty()){
		std::string temp_operator	=	this->expression_stack.pop();
		BinaryOperation temp(temp_operator, "Operator");
		this->shunting_yard_stack.push(temp);
	}
}

void ShuntingYard::toPN(){
	while(!this->shunting_yard_stack.isEmpty()){
		this->ordered_shunting_yard_stack.push(this->shunting_yard_stack.getTop());
		this->shunting_yard_stack.pop();
	}
}

void ShuntingYard::postFix(){
	while(!this->ordered_shunting_yard_stack.isEmpty()){
		switch(this->ordered_shunting_yard_stack.getTop().getBinaryOperation()[0]){
			case '+':{
				std::string r	=	"Added " + this->result_stack.getTop().toString() + " and ";
				this->result_stack.pop();
				r				=	r + this->result_stack.getTop().toString();
				this->result_stack.pop();
				BinaryOperation temp("+", "A", "B", "Operator");
				r				=	r + " to get a value of " + temp.toString();
				std::cout << r << std::endl;
				this->result_stack.push(temp);
				break;
			}
			case '-':{
				std::string r	=	"Subtracted " + this->result_stack.getTop().toString() + " and ";
				this->result_stack.pop();
				r				=	r + this->result_stack.getTop().toString();
				this->result_stack.pop();
				BinaryOperation temp("-", "A", "B", "Operator");
				r				=	r + " to get a value of " + temp.toString();
				std::cout << r << std::endl;
				this->result_stack.push(temp);
				break;
			}
			case '*':{
				std::string r	=	"Multiplied " + this->result_stack.getTop().toString() + " and ";
				this->result_stack.pop();
				r				=	r + this->result_stack.getTop().toString();
				this->result_stack.pop();
				BinaryOperation temp("*", "A", "B", "Operator");
				r				=	r + " to get a value of " + temp.toString();
				std::cout << r << std::endl;
				this->result_stack.push(temp);
				break;
			}
			case '/':{
				std::string r	=	"Divided " + this->result_stack.getTop().toString() + " and ";
				this->result_stack.pop();
				r				=	r + this->result_stack.getTop().toString();
				this->result_stack.pop();
				BinaryOperation temp("/", "B", "A", "Operator");
				r				=	r + " to get a value of " + temp.toString();
				std::cout << r << std::endl;
				this->result_stack.push(temp);
				break;
			}
			case '^':{
				std::string r	=	" to the power of " + this->result_stack.getTop().toString();
				this->result_stack.pop();
				r				=	"Took " + this->result_stack.getTop().toString() + r;
				this->result_stack.pop();
				BinaryOperation temp("^", "A", "B", "Operator");
				r				=	r + " to get a value of " + temp.toString();
				std::cout << r << std::endl;
				this->result_stack.push(temp);
				break;
			}
			default:
				this->result_stack.push(this->ordered_shunting_yard_stack.getTop());
				break;
		}

		this->ordered_shunting_yard_stack.pop();
	}
	this->result_stack.toString();
}

std::vector<BinaryOperation> ShuntingYard::getShuntingYard(){
	return this->operations;
}

void printVector(std::vector<std::string> v){
	unsigned int length	=	v.size();
	for(unsigned int i = 0; i < length; i++){
		std::cout << v[i] << std::endl;
	}
}

void printVector(std::vector<BinaryOperation> v){
	unsigned int length	=	v.size();
	for(unsigned int i = 0; i < length; i++){
		printf("i: %i\t", i);
		std::cout << v[i].toString() << std::endl;
	}
}
int countLogs(std::string str){
	int c	=	0;
	for(unsigned int i = 0; i < str.length(); i++){
		if(str[i] == 'l'){
			c++;
		}
	}
	return c;
}
int countLParens(std::string str){
	int c	=	0;
	for(unsigned int i = 0; i < str.length(); i++){
		if(str[i] == '('){
			c++;
		}
	}
	return c;
}
int countRParens(std::string str){
	int c	=	0;
	for(unsigned int i = 0; i < str.length(); i++){
		if(str[i] == ')'){
			c++;
		}
	}
	return c;
}

void trimParens(std::string* i){
	if((*i)[0] == '('){
		int c	=	0;
		for(unsigned int j = 0; j < i->length(); j++){
			if((*i)[j] == '('){
				c++;
			}else{
				break;
			}
		}
		*i	=	i->substr(c, i->length()-c-c);
	}
}

bool isNumber(std::string str){
	unsigned int c				=	str.length();
	unsigned int decimal_count	=	0;
	for(unsigned int i = 0; i < c; i++){
		if(!(str[i] < 57 && str[i] > 47)){
			return false;
		}
	}
	return true;
}
