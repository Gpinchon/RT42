# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarbari <mbarbari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/07 16:55:33 by mbarbari          #+#    #+#              #
#    Updated: 2017/02/07 14:30:41 by mbarbari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CX ?= clang++
CP = cp

NAME = libjson.a

CFLAGS += -Wall -Wextra -Werror -Iinc/ -Ilibft/include

PARSE_SRCS = 	src/foreach.c \
    			src/free_parser.c \
    			src/parse_function.c \
    			src/parse_type.c \
    			src/parser.c

PARSE_INCS = 	inc/parser.h \
  				inc/parser_union.h

COM_OBJS = $(patsubst src/%.c,obj/%.o,$(PARSE_SRCS))

LIBFT_PATH = ./libft/

RM ?= rm -f
MKDIR ?= mkdir

all: $(NAME)

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

$(LIBFT_PATH)/libft.a:
	$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(COM_OBJS)
	$(CP) $(LIBFT_PATH)libft.a $(NAME)
	$(AR) -rcs $(NAME) $?

obj/%.o: src/%.c $(LIBFT_PATH)/libft.a $(PARSE_INCS)
	$(MKDIR) -p $(dir $@)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	$(RM) $(COM_OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) cli
	$(RM) $(COM_OBJS)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: clean fclean re all
