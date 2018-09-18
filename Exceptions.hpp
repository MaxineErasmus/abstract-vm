/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14/37/56 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/12 17:33:32 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <stdexcept>

//LEXER

class FileOpenFailException : public std::exception {
	const char 			*what() const throw(){
		return "Lexer::FileOpenFailException";
	}
};

class InvalidInputException : public std::exception {
	const char 			*what() const throw(){
		return "Lexer::InvalidInputException";
	}
};

class NoExitFoundException : public std::exception {
	const char 			*what() const throw(){
		return "Lexer::NoExitFoundException";
	}
};

//CALCULATOR

class AssertFalseException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::AssertFalseException";
	}
};

class AssertEmptyStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::AssertEmptyStackException";
	}
};

class PopEmptyStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::PopEmptyStackException";
	}
};

class PrintEmptyStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::PrintEmptyStackException";
	}
};

class PrintNotInt8Exception : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::PrintNotInt8Exception";
	}
};

class AddLessThanTwoOnStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::Add::LessThanTwoOnStackException";
	}
};

class SubLessThanTwoOnStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::Sub::LessThanTwoOnStackException";
	}
};

class MulLessThanTwoOnStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::Mul::LessThanTwoOnStackException";
	}
};

class DivLessThanTwoOnStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::Div::LessThanTwoOnStackException";
	}
};

class ModLessThanTwoOnStackException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::Mod::LessThanTwoOnStackException";
	}
};


class OverflowException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::OverflowException";
	}
};

class UnderflowException : public std::exception {
	const char 			*what() const throw(){
		return "Calculator::UnderflowException";
	}
};

//OPERAND

class DivZeroException : public std::exception {
	const char 			*what() const throw(){
		return "Operand::DivZeroException";
	}
};

class ModZeroException : public std::exception {
	const char 			*what() const throw(){
		return "Operand::ModZeroException";
	}
};

#endif
