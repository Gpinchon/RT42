# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/13 17:17:47 by gpinchon          #+#    #+#              #
#    Updated: 2016/11/15 11:28:35 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	RT
SRC		=	./src/main.c				\
			./src/light_computation.c	\
			./src/new.c					\
			./src/new2.c				\
			./src/destroy.c

OBJ		=	$(SRC:.c=.o)
CC		=	gcc
INCLUDE	=	$(addprefix -I, $(wildcard ./libs/*/include/)) -I./include/
LIBDIR	=	$(wildcard ./libs/*)
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -lSDLframework -lSDL2main -lSDL2 -lGL -lm
CFLAGS	=	-Ofast -Wall -Wextra -Werror $(INCLUDE)

$(NAME): $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) && ) true
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) clean && ) true

fclean:
	rm -rf $(OBJ) $(NAME)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) fclean && ) true

re: fclean $(NAME)

.PHONY: all clean fclean re
