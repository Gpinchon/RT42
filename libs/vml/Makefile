# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/13 17:53:01 by gpinchon          #+#    #+#              #
#    Updated: 2017/01/20 17:36:56 by gpinchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libvml.a
SRC		=	./src/mat/identity.c		\
			./src/mat/zero.c			\
			./src/mat/adjugate.c		\
			./src/mat/minors.c			\
			./src/mat/convert.c			\
			./src/mat/cofactor.c		\
			./src/mat/combine.c			\
			./src/mat/inverse.c			\
			./src/mat/mult.c			\
			./src/mat/mult_vec2.c		\
			./src/mat/mult_vec3.c		\
			./src/mat/mult_vec4.c		\
			./src/mat/fmult.c			\
			./src/mat/new.c				\
			./src/mat/creation.c		\
			./src/mat/rotation.c		\
			./src/mat/scale.c			\
			./src/mat/shear.c			\
			./src/mat/determinant.c		\
			./src/mat/projection.c		\
			./src/mat/transpose.c		\
			./src/vec/new.c				\
			./src/vec/inverse.c			\
			./src/vec/reflect.c			\
			./src/vec/refract.c			\
			./src/vec/div.c				\
			./src/vec/fdiv.c			\
			./src/vec/proj.c			\
			./src/vec/add.c				\
			./src/vec/fadd.c			\
			./src/vec/cross.c			\
			./src/vec/dot.c				\
			./src/vec/length.c			\
			./src/vec/negate.c			\
			./src/vec/normalize.c		\
			./src/vec/orthogonal.c		\
			./src/vec/saturate.c		\
			./src/vec/sub.c				\
			./src/vec/convert.c			\
			./src/vec/mult.c			\
			./src/vec/scale.c			\
			./src/vec/pow.c				\
			./src/vec/distance.c		\
			./src/vec/interp.c			\
			./src/ray/new.c				\
			./src/ray/new_primitives.c	\
			./src/ray/new_primitives2.c	\
			./src/ray/new_primitives3.c	\
			./src/ray/calc.c			\
			./src/ray/primitives.c		\
			./src/ray/primitives2.c		\
			./src/ray/normals.c			\
			./src/transform/new.c		\
			./src/transform/update.c	\
			./src/interp_functions.c	\
			./src/float_functions.c		\
			./src/vml_memset.c

TESTSRC	=	./test/test.c
TESTOBJ	= $(TESTSRC:.c=.o)
TESTNAM	= vml_test

OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Ofast -Wall -Wextra -Wall -I ./include


$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
%.o: %.c
	@echo -n Compiling $@...
	@($(CC) $(CFLAGS) -o $@ -c $<)
	@echo "$(OK_STRING)"

test:
	$(CC) $(CFLAGS) $(TESTSRC) -L . -lvml -o vml_test

all: $(NAME) test

clean:
	rm -rf $(OBJ) $(TESTOBJ)

fclean: clean
	rm -rf $(NAME) $(TESTNAM)

re: fclean $(NAME)

.PHONY: all test clean fclean re