# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pborrull <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 14:09:31 by pborrull          #+#    #+#              #
#    Updated: 2024/08/01 14:10:27 by pborrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c  ft_atoi.c \
  	ft_strdup.c ft_substr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_strnstr.c ft_strtrim.c \
	ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c get_next_line.c \
	get_next_line_utils.c printf/ft_printf_i.c printf/ft_printf_p.c \
	printf/ft_printf.c printf/ft_extra.c printf/ft_printf_x.c \
	printf/ft_printf_xx.c printf/ft_printf_s.c printf/ft_printf_u.c
OBJECTS = $(SOURCES:.c=.o)

INCLUDES = libft.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	make -C printf/

$(NAME): $(OBJECTS) Makefile
	$(AR) -rcs $@ $(OBJECTS)

%.o: %.c $(INCLUDES) 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	make clean -C printf/
	rm -f *.o 
fclean: clean
	make fclean -C printf/
	rm -f *.o $(NAME) libft.h.gch
re: fclean all

.PHONY: all clean fclean re
