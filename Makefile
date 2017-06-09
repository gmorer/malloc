# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/06 11:00:01 by gmorer            #+#    #+#              #
#    Updated: 2017/06/09 20:26:47 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so
CC = clang
CFLAGS= -Weverything -fsanitize=address
CPATH = src/
HPATH = inc/
OPATH = obj/
CFILES =	malloc.c\
			malloc_lib.c\
			realloc.c\
			free.c\
			new_elem.c
HFILES = inc/malloc.h
INC = $(addprefix -I , $(HPATH))
OBJ = $(addprefix $(OPATH), $(CFILES:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)   		        #a supprimer pour le rendu final
	#$(CC) -shared $(OBJ) $(CFLAGS) -o $(NAME)          #a uncomment pour le rendu final
	#ln -s libft_malloc_$(HOSTTYPE).so libft_malloc.so  #a uncomment pour le rendu final

$(OPATH)%.o : $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) -g $(INC) $< -c -o $@

clean :
	rm -f $(OBJ)
	rm -f libft_malloc.so

fclean : clean
	rm -f $(NAME)

re : fclean all
