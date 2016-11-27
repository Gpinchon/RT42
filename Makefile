# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/13 17:17:47 by gpinchon          #+#    #+#              #
#    Updated: 2016/11/27 15:58:50 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	RT
SRC		=	./src/main.c				\
			./src/light_computation.c	\
			./src/new.c					\
			./src/new2.c				\
			./src/destroy.c				\
			./src/clear.c				\
			./src/put_pixel.c

OBJ		=	$(SRC:.c=.o)
CC		=	gcc
INCLUDE	=	$(addprefix -I, $(wildcard ./libs/*/include/)) -I./include/
LIBDIR	=	$(wildcard ./libs/*)

CFLAGS	=	-g -Wall -Wextra -Werror $(INCLUDE)

ifeq ($(OS), Windows_NT)
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -lmingw32 -lSDLframework -lSDL2main -lSDL2  -lopengl32 -lm
else
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -lSDLframework -lSDL2main -lSDL2 -lGL -lm
endif

$(NAME): $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) && ) true
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)

pull:
	git pull && git submodule foreach git pull origin master

clean:
	rm -rf $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) clean && ) true

fclean:
	rm -rf $(OBJ) $(NAME)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) fclean && ) true

re: fclean $(NAME)

.PHONY: all clean fclean re
