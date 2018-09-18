# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rerasmus <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/25 10:08:23 by rerasmus          #+#    #+#              #
#    Updated: 2018/07/08 14:25:54 by rerasmus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG = avm
MAIN = main.cpp
CLASSES = Calculator.cpp Lexer.cpp Operand.cpp

all:
	@ clang++ -Wall -Werror -Wextra $(MAIN) $(CLASSES) -o $(PROG)
	@ clear

clean:
	@ rm -rf $(PROG)
	@ clear

re: clean all
	@ clear
