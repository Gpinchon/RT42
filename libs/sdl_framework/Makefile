OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Ofast -Wall -Wextra -Werror -I ./include
NAME 	= libSDLframework.a

ifeq ($(OS), Windows_NT)
	LIBS	= -lmingw32 -lSDL2main -lSDL2 -lopengl32
	TEST	= sdl_framework.exe
	MAKE	= mingw32-make
	RM		= del
	RMDIR	= rmdir
	MV		= move
	SRC		=	srcs\new_framework.c		\
				srcs\new_window.c			\
				srcs\new_image.c			\
				srcs\destroy_framework.c	\
				srcs\destroy_window.c		\
				srcs\destroy_image.c		\
				srcs\clear_window.c			\
				srcs\load_image.c			\
				srcs\attach_image.c			\
				srcs\put_image.c			\
				srcs\fill_image.c			\
				srcs\get_pixel.c			\
				srcs\put_pixel.c			\
				srcs\new_color.c			\
				srcs\objects.c				\
				srcs\loop.c					\
				srcs\hook.c					\
				srcs\new_callback.c			\
				srcs\internal_memory.c		\
				srcs\internal_string.c		\
				srcs\errors.c
else
	LIBS	= -lSDL2main -lSDL2 -lGL
	TEST 	= sdl_framework
	MAKE	= make
	RM		= rm -rf
	RMDIR	= rm -rf
	MV		= mv
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
				srcs/hook.c					\
				srcs/new_callback.c			\
				srcs/internal_memory.c		\
				srcs/internal_string.c		\
				srcs/errors.c
endif

$(NAME): $(OBJ) test.o
	@echo $(OS)
	ar rc $(NAME) $(OBJ)
	mkdir lib && $(MV) libSDLframework.a lib/libSDLframework.a
	@$(CC) $(CFLAGS) $(OBJ) test.o $(LIBS) -o $(TEST)

printos:
	@echo $(OS)

fclean:
	$(RM) $(OBJ) $(NAME) $(TEST)
	$(RMDIR) lib

re:fclean
	$(MAKE)