# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/23 19:39:12 by gpinchon          #+#    #+#              #
#    Updated: 2017/02/10 21:04:56 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Ofast -Wall -Wextra -Werror -I ./include
NAME 	= libSDLframework.a
SRC		=	srcs/new_framework.c		\
			srcs/new_window.c			\
			srcs/new_image.c			\
			srcs/destroy_framework.c	\
			srcs/destroy_window.c		\
			srcs/destroy_image.c		\
			srcs/clear_window.c			\
			srcs/load_image.c			\
			srcs/attach_image.c			\
			srcs/put_image.c			\
			srcs/fill_image.c			\
			srcs/get_pixel.c			\
			srcs/put_pixel.c			\
			srcs/new_color.c			\
			srcs/objects.c				\
			srcs/loop.c					\
			srcs/hook_get.c				\
			srcs/hook_set_keys.c		\
			srcs/hook_set_mouse.c		\
			srcs/hook_set_system.c		\
			srcs/new_callback.c			\
			srcs/internal_memory.c		\
			srcs/internal_string.c		\
			srcs/check_event.c			\
			srcs/errors.c

ifeq ($(OS), Windows_NT)
	LIBS	= -lmingw32 -lSDL2main -lSDL2 -lopengl32
	TEST	= sdl_test.exe
	MAKE	= mingw32-make
	RM		= rm -rf
	MV		= move
else
	LIBS	= -lSDL2main -lSDL2 -lGL
	TEST 	= sdl_test
	MAKE	= make
	RM		= rm -rf
	MV		= mv
endif

ifeq ($(shell uname -s), Darwin)
CFLAGS	= -Ofast -Wall -Wextra -Werror -I ~/.brew/include -I ./include
LIBS	= -L ~/.brew/lib -lSDL2
endif

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

test: test.o
	@$(CC) $(CFLAGS) test.o -L ./ -lSDLframework $(LIBS) -o $(TEST)

printos:
	@echo $(OS)

clean:
	$(RM) $(OBJ) test.o

fclean:
	$(RM) $(OBJ) $(NAME) $(TEST)

re:fclean
	$(MAKE)
