/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculator.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16/35/02 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:37:03 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Calculator.hpp"

Calculator::Calculator(){
	//setup function pointers
	this->create[Int8] = &Calculator::createInt8;
	this->create[Int16] = &Calculator::createInt16;
	this->create[Int32] = &Calculator::createInt32;
	this->create[Float] = &Calculator::createFloat;
	this->create[Double] = &Calculator::createDouble;

	TOKEN			token;
	Lexer			lex;
	std::string		input;
	for (;;){
		std::getline(std::cin, input);
		
		if (input == "exit")
			break;
		token = lex.getToken(input);
		if (token.command == "exit")
			break;
		
		if (lex.HasErrors()){
			lex.PrintTokens();
			throw InvalidInputException();
		}else{
			if (this->_tokens.size() > 0)
				this->_tokens.pop_back();
			this->_tokens.push_back(token);
			run();
		}
	}
}

Calculator::Calculator(std::string fname){
	//setup function pointers 
	this->create[Int8] = &Calculator::createInt8;
	this->create[Int16] = &Calculator::createInt16;
	this->create[Int32] = &Calculator::createInt32;
	this->create[Float] = &Calculator::createFloat;
	this->create[Double] = &Calculator::createDouble;

	Lexer	lex(fname);
	if (lex.HasErrors()){
		lex.PrintTokens();
		throw InvalidInputException();
	}else{
		this->_tokens = lex.getTokens();
		run();
	}
}

Calculator::Calculator(Calculator const &src){
	*this = src;	
}

Calculator::~Calculator(){
	for (size_t i = 0; i < this->_stack.size(); i++){
		delete this->_stack[i];
		this->_stack[i];
	}
}

//FACTORY

IOperand const		*Calculator::createOperand(eOperandType type, std::string const &value) const{
	long double ld = std::stold(value);

	if (hasOverflow(type, ld))
		throw OverflowException();
	else if (hasUnderflow(type, ld))
		throw UnderflowException();

	return (this->*create[type])(value);
}

IOperand const 		*Calculator::createInt8(std::string const &value) const{
	int c = std::stoi(value);
	return new Operand(Int8, std::to_string(c));
}
IOperand const 		*Calculator::createInt16(std::string const &value) const{
	short sh = std::stoi(value);
	return new Operand(Int16, std::to_string(sh));
}
IOperand const		*Calculator::createInt32(std::string const &value) const{
	int i = std::stoi(value);
	return new Operand(Int32, std::to_string(i));
}
IOperand const		*Calculator::createFloat(std::string const &value) const{
	std::stringstream conv;
	float f = std::stof(value);

	conv.precision(value.length() < 8 ? value.length() : 8);
	conv << f;
	return new Operand(Float, conv.str());
}
IOperand const		*Calculator::createDouble(std::string const &value) const{
	std::stringstream conv;
	double d = std::stod(value);

	conv.precision(value.length() < 16 ? value.length() : 16);
	conv << d;
	return new Operand(Double, conv.str());
}

//STACK

void				Calculator::push(std::string const &type, std::string const &value){
	this->_stack.push_back(createOperand(toType(type), value));
}

void				Calculator::assert(std::string const &value){
	if (this->_stack.size() == 0)
		throw AssertEmptyStackException();

	long double a = std::stold(this->_stack.back()->toString());
	long double b = std::stold(value);

	if (a != b)
		throw AssertFalseException();
}

void				Calculator::pop(){
	if (this->_stack.size() == 0)
		throw PopEmptyStackException();

	delete this->_stack.back();
	this->_stack.pop_back();
}

void				Calculator::dump(){
	std::string			str;
	std::stringstream	conv;
	unsigned long		precision;
	long double			ld;

	for (int i = this->_stack.size() - 1; i > -1; i--){
		str = this->_stack[i]->toString();
		precision = this->_stack[i]->getPrecision();
		conv.str(std::string());

		if (precision > 2){
			ld = std::stold(str);
			conv.precision(str.length() < precision ? str.length() : precision);
			conv << ld;
			str = conv.str();
			std::cout.precision(str.length() < precision ? str.length() : precision);
		}
		std::cout << str << std::endl;
	}
}

void				Calculator::print(){
	if (this->_stack.size() == 0)
		throw PrintEmptyStackException();
	if (this->_stack.back()->getType() != Int8)
		throw PrintNotInt8Exception();

	std::cout << static_cast<char>(std::stoi(this->_stack.back()->toString())) << std::endl;
}

//MATH

void				Calculator::add(){
	if (this->_stack.size() < 2)
		throw AddLessThanTwoOnStackException();

	const IOperand *a = this->_stack.back();
	this->_stack.pop_back();
	const IOperand *b = this->_stack.back();
	this->_stack.pop_back();
	
	this->_stack.push_back(*a+*b);
	
	delete a;
	delete b;
}

void				Calculator::sub(){
	if (this->_stack.size() < 2)
		throw SubLessThanTwoOnStackException();

	const IOperand *a = this->_stack.back();
	this->_stack.pop_back();
	const IOperand *b = this->_stack.back();
	this->_stack.pop_back();

	this->_stack.push_back(*a-*b);

	delete a;
	delete b;
}

void				Calculator::mul(){
	if (this->_stack.size() < 2)
		throw MulLessThanTwoOnStackException();

	const IOperand *a = this->_stack.back();
	this->_stack.pop_back();
	const IOperand *b = this->_stack.back();
	this->_stack.pop_back();

	this->_stack.push_back((*a)*(*b));

	delete a;
	delete b;
}

void				Calculator::div(){
	if (this->_stack.size() < 2)
		throw DivLessThanTwoOnStackException();

	const IOperand *a = this->_stack.back();
	this->_stack.pop_back();
	const IOperand *b = this->_stack.back();
	this->_stack.pop_back();

	this->_stack.push_back((*a)/(*b));

	delete a;
	delete b;
}

void				Calculator::mod(){
	if (this->_stack.size() < 2)
		throw ModLessThanTwoOnStackException();

	const IOperand *a = this->_stack.back();
	this->_stack.pop_back();
	const IOperand *b = this->_stack.back();
	this->_stack.pop_back();

	this->_stack.push_back((*a)%(*b));

	delete a;
	delete b;
}

//FUNCTIONS

void				Calculator::run(){
	for (unsigned long i = 0; i < this->_tokens.size(); i++){
		//stack
		if (this->_tokens[i].command == "exit")
			break;
		else if (this->_tokens[i].command == "push")
			push(this->_tokens[i].type, this->_tokens[i].value);
		else if (this->_tokens[i].command == "assert")
			assert(this->_tokens[i].value);
		else if (this->_tokens[i].command == "pop")
			pop();
		else if (this->_tokens[i].command == "dump")
			dump();
		else if (this->_tokens[i].command == "print")
			print();

		//math
		else if (this->_tokens[i].command == "add")
			add();
		else if (this->_tokens[i].command == "sub")
			sub();
		else if (this->_tokens[i].command == "mul")
			mul();
		else if (this->_tokens[i].command == "div")
			div();
		else if (this->_tokens[i].command == "mod")
			mod();
	}
}

eOperandType		Calculator::toType(std::string const &type){
	if (type == "int8")
		return Int8;
	else if (type == "int16")
		return Int16;
	else if (type == "int32")
		return Int32;
	else if (type == "float")
		return Float;
	else if (type == "double")
		return Double;
	else
		return Int8;
}

bool				Calculator::hasOverflow(eOperandType type, long double const &value) const{
	switch (type){
		case Int8:
			if (value > CHAR_MAX)
				return true;
			break;
		case Int16:
			if (value > SHRT_MAX)
				return true;
			break;
		case Int32:
			if (value > INT_MAX)
				return true;
			break;
		case Float:
			if (value > FLT_MAX)
				return true;
			break;
		case Double:
			if (value > DBL_MAX)
				return true;
			break;
		default:
			return false;
	}
	return false;
}

bool				Calculator::hasUnderflow(eOperandType type, long double const &value) const{
	switch (type){
		case Int8:
			if (value < CHAR_MIN)
				return true;
			break;
		case Int16:
			if (value < SHRT_MIN)
				return true;
			break;
		case Int32:
			if (value < INT_MIN)
				return true;
			break;
		case Float:
			if (value < FLT_MIN)
				return true;
			break;
		case Double:
			if (value < DBL_MIN)
				return true;
			break;
		default:
			return false;
	}
	return false;
}


