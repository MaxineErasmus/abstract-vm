/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 10/43/59 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:36:59 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

Operand::Operand() {}

Operand::Operand(eOperandType type, std::string value): _type(type), 
	_value(value){
		switch (type){
			case Int8:
				this->_precision = 0;
				break;
			case Int16:
				this->_precision = 1;
				break;
			case Int32:
				this->_precision = 2;
				break;
			case Float:
				this->_precision = 8;
				break;
			case Double:
				this->_precision = 16;
				break;
		}
}

Operand::Operand(Operand const &src) {
	*this = src;	
}

Operand::~Operand() {
}

Operand				&Operand::operator=(Operand const &src) {
	if (this != &src){
		*this = src;
	}
	return (*this);
}

//GETTERS

int					Operand::getPrecision() const{
	return this->_precision;
}

eOperandType		Operand::getType(void) const{
	return this->_type;
}

//FUNCTIONS

IOperand const		*Operand::operator+(IOperand const &rhs) const{
	long double			a = std::stold(this->_value);
	long double			b = std::stold(rhs.toString());
	long double			ans = a+b;

	eOperandType		type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

	return new Operand(type, std::to_string(ans));
}

IOperand const		*Operand::operator-(IOperand const &rhs) const{
	long double a = std::stold(this->_value);
	long double b = std::stold(rhs.toString());
	long double ans = a-b;

	eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

	return new Operand(type, std::to_string(ans));
}

IOperand const		*Operand::operator*(IOperand const &rhs) const{
	long double a = std::stold(this->_value);
	long double b = std::stold(rhs.toString());
	long double ans = a*b;

	eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

	return new Operand(type, std::to_string(ans));
}

IOperand const		*Operand::operator/(IOperand const &rhs) const{
	long double a = std::stold(this->_value);
	long double b = std::stold(rhs.toString());

	if (a == 0)
		throw DivZeroException();

	long double ans = b/a;

	eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

	return new Operand(type, std::to_string(ans));
}

IOperand const		*Operand::operator%(IOperand const &rhs) const{
	long double a = std::stold(this->_value);
	long double b = std::stold(rhs.toString());

	if (a == 0)
		throw ModZeroException();

	long double ans = std::fmod(b,a);

	eOperandType type = this->getPrecision() > rhs.getPrecision() ? this->getType() : rhs.getType();

	return new Operand(type, std::to_string(ans));
}

std::string const	&Operand::toString(void) const{
	return this->_value;
}

