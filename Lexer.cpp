/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rerasmus   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14/01/56 by rerasmus          #+#    #+#             */
/*   Updated: 2018/07/13 15:30:37 by rerasmus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer() {}

Lexer::Lexer(std::string fname) : _lineIndex(0), _hasErrors(false) {
	std::string		line;
	std::ifstream	file(fname);
	TOKEN			token;
	int				comment = -1;

	if (file.is_open()){
		while (std::getline(file,line)){
			this->_lineIndex++;
			comment = line.find(";");

			if (comment > -1){
				if (line.substr(0, comment).length() > 0){
					this->_tokens.push_back(Tokenize(line.substr(0, comment)));
				}
				if (line.substr(comment, 2) == ";;"){
					token.command = "exit";
					token.type = "input";
					token.value = ";;";
					this->_tokens.push_back(token);
					this->_hasExit = true;
				}
				comment = -1;
			}else if (line.length() > 0){
				this->_tokens.push_back(Tokenize(line));
			}
		}
	}else
		throw FileOpenFailException();
	file.close();
	if (!this->_hasExit)
		throw NoExitFoundException();
}

Lexer::Lexer(Lexer const & src) {
	*this = src;	
}

Lexer::~Lexer() {}

Lexer			&Lexer::operator=(Lexer const & src) {
	if (this != &src){
		*this = src;
	}
	return (*this);
}

//GETTERS

TOKEN					Lexer::getToken(std::string str){
	int					comment = -1;
	TOKEN				token;

	comment = str.find(";");
	if (comment > -1){
		if (str.substr(0, comment).length() > 0){
			token = Tokenize(str.substr(0, comment));
		}
		if (str.substr(comment, 2) == ";;")
			token.command = "exit";
	}else if (str.length() > 0){
		token = Tokenize(str);
	}
	return token;
}

std::vector<TOKEN>		Lexer::getTokens() const{
	return this->_tokens;
}

//FUNCTIONS

TOKEN					Lexer::Tokenize(std::string const str){
	std::smatch			match;
	TOKEN				token;

	std::regex			rgx1("^\\s*(push|assert)\\s+(int8|int16|int32|double|float)\\s*\\(\\s*(-?\\d+\\.?\\d*)\\s*\\)\\s*$");
	std::regex			rgx2("^\\s*(pop|dump|print)\\s*$");
	std::regex			rgx3("^\\s*(add|sub|mul|div|mod)\\s*$");
	std::regex			rgxExit("^\\s*(exit)\\s*$");

	if (std::regex_search(str.begin(), str.end(), match, rgx1)){}
	else if (std::regex_search(str.begin(), str.end(), match, rgx2)){}
	else if (std::regex_search(str.begin(), str.end(), match, rgx3)){}
	else if (std::regex_search(str.begin(), str.end(), match, rgxExit)){
		this->_hasExit = true;
		token.command = "exit";
	}
	else{
		this->_hasErrors = true;

		token.command = "[Error]";
		token.type = "Line ";
		token.type = token.type + std::to_string(this->_lineIndex);
		token.type = token.type + " :";
		token.value = str;
	}

	if (match[1].length())
		token.command = match[1];
	if (match[2].length())
		token.type = match[2];
	if (match[3].length())
		token.value = match[3];

	return token;
}

void					Lexer::PrintTokens(){
	for (unsigned long i = 0; i < this->_tokens.size(); i++){
		std::cout << this->_tokens[i].command;
		if (this->_tokens[i].type.length())
			std::cout << " " << this->_tokens[i].type;
		if (this->_tokens[i].value.length())
			std::cout << " " << this->_tokens[i].value;
		std::cout << std::endl;
	}
}

bool					Lexer::HasErrors() const{
	return this->_hasErrors;
}
