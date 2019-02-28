# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 18:36:00 by gfielder          #+#    #+#              #
#    Updated: 2019/02/27 21:46:49 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

filegen:
	clang -I. -L. -lft -o generate_test filegen.c main.c

mine:
	make -C ../get_next_line/libft/ fclean && make -C ../get_next_line/libft/
	clang -Wall -Wextra -Werror -I ../get_next_line/libft/includes -o get_next_line.o -c ../get_next_line/get_next_line.c
	clang -Wall -Wextra -Werror -I ../get_next_line/libft/includes -o file-printer.o -c file-printer.c
	clang -o test_mine file-printer.o get_next_line.o -I ../get_next_line/libft/includes -L ../get_next_line/libft/ -lft

dav:
	make -C validated-gnls/davhojt/libft/ fclean && make -C validated-gnls/davhojt/libft/
	clang -Wall -Wextra -Werror -I validated-gnls/davhojt/libft/includes -o get_next_line.o -c validated-gnls/davhojt/get_next_line.c
	clang -Wall -Wextra -Werror -I validated-gnls/davhojt/libft/includes -o file-printer.o -c file-printer.c
	clang -o test_davhojt file-printer.o get_next_line.o -I validated-gnls/davhojt/libft/includes -L validated-gnls/davhojt/libft/ -lft

