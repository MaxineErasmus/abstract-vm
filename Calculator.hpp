/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculator.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 09:50:00 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:34:37 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

# include <sstream>
# include <cfloat>
# include "Lexer.hpp"
# include "Operand.hpp"

class Calculator{
	private:
		std::vector<TOKEN>					_tokens;
		std::vector<const IOperand *>		_stack;

		//FUNCTIONS	
		IOperand const	*createInt8(std::string const &value) const;
		IOperand const	*createInt16(std::string const &value) const;
		IOperand const	*createInt32(std::string const &value) const;
		IOperand const	*createFloat(std::string const &value) const;
		IOperand const	*createDouble(std::string const &value) const;

	public:
		Calculator();
		Calculator(std::string fname);
		Calculator(Calculator const &src);
		~Calculator();
		
		//FUNCTIONS
		void			run();
		IOperand const	*createOperand(eOperandType type, std::string const &value) const;
		IOperand const	*(Calculator::*create[5])(std::string const &value) const;
		eOperandType	toType(std::string const &type);
		bool			hasOverflow(eOperandType type, long double const &value) const;
		bool			hasUnderflow(eOperandType type, long double const &value) const;

		//STACK
		void			push(std::string const &type, std::string const &value);
		void			assert(std::string const &value);
		void			pop();
		void			dump();
		void			print();

		//MATHEMATICS
		void			add();
		void			sub();
		void			mul();
		void			div();
		void			mod();
};

#endif
