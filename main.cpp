/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:06:01 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:34:10 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Exceptions.hpp"
#include "Lexer.hpp"
#include "Calculator.hpp"
#include "Operand.hpp"

int			main(int argc, char **argv){
	try{

		if (argc == 2)
			Calculator	calc(argv[1]);
		else
			Calculator	calc;

	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return (0);
}
