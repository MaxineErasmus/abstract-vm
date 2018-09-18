/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14/01/56 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:31:02 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include <fstream>
# include <regex>

# include "Exceptions.hpp"

struct	TOKEN{
	std::string		command;
	std::string		type;
	std::string		value;
};

class Lexer {
	private:
		unsigned int			_lineIndex;
		bool					_hasExit;
		bool					_hasErrors;
		std::vector<TOKEN>		_tokens;

	public:
		Lexer();
		Lexer(std::string fname);
		Lexer(Lexer const &src);
		~Lexer();
		Lexer & operator=(Lexer const &src);
	
		//GETTERS
		TOKEN					getToken(std::string str);
		std::vector<TOKEN>		getTokens() const;

		//FUNCTIONS
		TOKEN					Tokenize(std::string const str);
		void					PrintTokens();
		bool					HasErrors() const;
};

#endif
