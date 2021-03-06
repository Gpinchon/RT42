# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/13 17:17:47 by gpinchon          #+#    #+#              #
#    Updated: 2017/02/15 17:08:20 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	RT
SRC		=	./src/main.c					\
			./src/cast_ray.c				\
			./src/cast_light_ray.c			\
			./src/area_lighting.c			\
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
			./src/blur.c					\
			./src/ssao.c					\
			./src/render.c					\
			./src/create_scene.c			\
			./src/fill_scene.c				\
			./src/fill_mesh.c				\
			./src/json_to_math.c			\
			./src/json_to_prim.c			\
			./src/mthread.c

OBJ		=	$(SRC:.c=.o)
CC		=	gcc

INCLUDE_REP = 	./include \
				./libs/json/inc \
				./libs/ezmem/include \
				./libs/sdl_framework/include \
				./libs/vml/include

INCLUDE	=	$(addprefix -I, $(INCLUDE_REP)) -I./include/

LIBDIR	=	./libs/json/ \
			./libs/ezmem/ \
			./libs/sdl_framework/ \
			./libs/vml/

LIBFILE	=	./libs/json/libjson.a \
			./libs/ezmem/libezmem.a \
			./libs/sdl_framework/libSDLframework.a \
			./libs/vml/libvml.a

ifeq ($(OS), Windows_NT)
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -ljson -lmingw32 -lSDLframework -lSDL2main -lSDL2  -lopengl32 -lm
else ifeq ($(shell uname -s), Darwin)
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -ljson -L ~/.brew/lib -lSDLframework -lSDL2 -lm -lpthread
INCLUDE	=	-I ~/.brew/include $(addprefix -I, $(INCLUDE_REP)) -I./include/
else
LIBS	=	$(addprefix -L , $(LIBDIR)) -lezmem -lvml -ljson -lSDLframework -lSDL2main -lSDL2 -lGL -lm -lpthread
INCLUDE	=	$(addprefix -I, $(INCLUDE_REP)) -I./include/
endif

CFLAGS	=	-Ofast -ffast-math -Wall -Wextra -Werror $(INCLUDE)

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

all: $(NAME)

$(NAME): $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) && ) true
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)


pull:
	git fetch --all && git pull origin master

clean:
	rm -rf $(OBJ)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) clean && ) true

fclean:
	rm -rf $(OBJ) $(NAME)
	$(foreach dir, $(LIBDIR), $(MAKE) -C $(dir) fclean && ) true

re: fclean $(NAME)

.PHONY: all clean fclean re
