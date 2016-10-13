# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/13 17:53:01 by gpinchon          #+#    #+#              #
#    Updated: 2016/10/13 17:55:38 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= VML.a
SRC		=	./src/mat_init.c		\
			./src/mat_operations.c	\
			./src/vec_add.c			\
			./src/vec_cross.c		\
			./src/vec_dot.c			\
			./src/vec_length.c		\
			./src/vec_normalize.c	\
			./src/vec_sub.c			\
			./src/vecmat_convert.c	\
			./src/vecmat_mult.c

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Ofast -Wall -Wextra -Wall


$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
%.o: %.c
	@echo -n Compiling $@...
	@($(CC) $(CFLAGS) -o $@ -c $<)
	@echo "$(OK_STRING)"

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)