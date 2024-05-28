# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbotargu <pbotargu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
<<<<<<< HEAD
#    Created: 2024/04/25 13:50:18 by pbotargu          #+#    #+#              #
#    Updated: 2024/05/21 14:17:07 by pborrull         ###   ########.fr        #
=======
#    Created: 2024/03/08 09:26:08 by pborrull          #+#    #+#              #
#    Updated: 2024/04/23 14:46:51 by pborrull         ###   ########.fr        #
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752
#                                                                              #
# **************************************************************************** #

NAME = minishell

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

<<<<<<< HEAD
INCS = -I./include/ -I./include/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./include/Libft -lft
LIBFT = include/libft	
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline
SRCDIR = src/
OBJDIR = obj/
=======
SOURCE := main.c signals.c get_tok.c utils.c blt_echo.c blt_env.c blt_pwd.c blt_exit.c blt_unset.c blt_export.c expansor.c
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752

SRC_L = blt_cd.c blt_echo.c blt_env.c blt_exit.c blt_export.c blt_pwd.c blt_unset.c expansor.c get_tok.c main.c signals.c utils.c get_list.c quotes.c executor/executor.c executor/executor_utils.c builtins/builtins_utils.c exit_status.c

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all:
	@make -C $(LIBFT) > /dev/null
	@make $(NAME)

$(OBJDIR)%.o: %.c
			
			@mkdir -p $(@D)
			@gcc $(CFLAGS) $(INCS) -c $< -o $@
			@echo "$(GREEN)[OK]       $(CYAN)Compiled$(ORIGINAL)"

$(NAME): $(OBJECTS) Makefile 
			@mkdir -p $(@D)
			@gcc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
			@echo  "$(GREEN)[OK]       $(YELLOW)All Compiled$(ORIGINAL)"

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIBFT) > /dev/null
		@echo  "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

clean:
		@rm -rf $(OBJDIR)
		@make clean -C $(LIBFT) > /dev/null
		@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

re: fclean all

.PHONY: all clean fclean re
