/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 10/43/59 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:36:57 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include "Exceptions.hpp"
# include <sstream>
# include <climits>
# include <cmath>

class Operand : public IOperand {
	private:
		eOperandType	_type;
		std::string		_value;
		int				_precision;
		
	public:
		Operand();
		Operand(eOperandType type, std::string value);
		Operand(Operand const &src);
		~Operand();
		Operand					&operator=(Operand const &src);

		//GETTERS
		int						getPrecision() const;
		eOperandType			getType() const; 

		//FUNCTIONS
		IOperand const			*operator+(IOperand const &rhs) const; 
		IOperand const			*operator-(IOperand const &rhs) const; 
		IOperand const			*operator*(IOperand const &rhs) const; 
		IOperand const			*operator/(IOperand const &rhs) const; 
		IOperand const			*operator%(IOperand const &rhs) const;
		std::string const		&toString(void) const; 

};

#endif
