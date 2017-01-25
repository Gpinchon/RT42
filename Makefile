# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/13 17:17:47 by gpinchon          #+#    #+#              #
#    Updated: 2017/01/25 18:45:08 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	RT
SRC		=	./src/main.c					\
			./src/cast_ray.c				\
			./src/light_formulas.c			\
			./src/light_formulas1.c			\
			./src/compute_lighting.c		\
			./src/compute_point_color.c		\
			./src/refraction_reflection.c	\
			./src/texture_mapping.c			\
			./src/texture_mapping1.c		\
			./src/transform.c				\
			./src/materials.c				\
			./src/mtllib.c					\
			./src/mtllib1.c					\
			./src/mtllib2.c					\
			./src/mtllib3.c					\
			./src/new.c						\
			./src/new2.c					\
			./src/destroy.c					\
			./src/clear.c					\
			./src/put_pixel.c				\
			./src/random.c					\
			./src/uv.c						\
			./src/blit.c					\
			./src/print_progress.c			\
			./src/post.c					\
			./src/render.c

OBJ		=	$(SRC:.c=.o)
CC		=	gcc
INCLUDE	=	$(addprefix -I, $(wildcard ./libs/*/include/)) -I./include/
LIBDIR	=	$(wildcard ./libs/*)

CFLAGS	=	-O3 -ffast-math -Wall -Wextra -Werror $(INCLUDE)

ifeq ($(OS), Windows_NT)
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -lmingw32 -lSDLframework -lSDL2main -lSDL2  -lopengl32 -lm
else ifeq ($(shell uname -s), Darwin)
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -L ~/.brew/lib -lSDLframework -lSDL2 -lm
INCLUDE	=	-I ~/.brew/include $(addprefix -I, $(wildcard ./libs/*/include/)) -I./include/
else
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -lSDLframework -lSDL2main -lSDL2 -lGL -lm
endif

$(NAME): $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) && ) true
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

all: $(NAME)

pull:
	git pull
	git submodule update --init --recursive
	git submodule foreach git pull origin master

clean:
	rm -rf $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) clean && ) true

fclean:
	rm -rf $(OBJ) $(NAME)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) fclean && ) true

re: fclean $(NAME)

.PHONY: all clean fclean re
