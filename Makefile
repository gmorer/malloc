# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/06 11:00:01 by gmorer            #+#    #+#              #
#    Updated: 2017/06/06 13:28:35 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so
CC = clang
CFLAGS= -Weverything
CPATH = src/
HPATH = inc/
OPATH = obj/
CFILES =	malloc.c\
			realloc.c\
			free.c

HFILES = inc/malloc.h
INC = $(addprefix -I , $(HPATH))
OBJ = $(addprefix $(OPATH), $(CFILES:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)
	ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so

$(OPATH)%.o : $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(INC) $< -c -o $@

clean :
	rm -f $(OBJ)
	rm -f libft_malloc.so

fclean : clean
	rm -f $(NAME)

re : fclean all
