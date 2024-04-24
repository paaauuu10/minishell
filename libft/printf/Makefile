# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 11:02:04 by pborrull          #+#    #+#              #
#    Updated: 2023/10/26 11:09:44 by pborrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SOURCES = \
		  ft_printf.c ft_printf_i.c ft_printf_p.c ft_printf_s.c \
		  ft_printf_u.c ft_printf_x.c ft_printf_xx.c ft_extra.c
OBJECTS = $(SOURCES:.c=.o)

INCLUDES = ft_printf.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $@ $?

%.o: %.c $(INCLUDES) 
	$(CC) -c  $(CFLAGS) $?

clean:
	rm -f  $(OBJECTS) ft_printf.h.gch
fclean: clean
	rm -f $(NAME) ft_printf.h.gch

re: fclean all

.PHONY: all clean fclean re
