# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbotargu <pbotargu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 13:50:18 by pbotargu          #+#    #+#              #
#    Updated: 2024/08/06 14:51:42 by pbotargu         ###   ########.fr        #
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

INCS = -I./include/ -I./include/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./include/libft -lft
LIBFT = include/libft	
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline
SRCDIR = src/
OBJDIR = obj/

SRC_L = wait/wait.c redirections/redirections.c redirections/redir_utils.c redirections/check_redir.c blt_cd.c blt_echo.c blt_env.c blt_exit.c blt_export.c blt_pwd.c blt_unset.c expansor.c get_tok.c main.c signals.c utils.c get_list.c quotes.c quotes2.c executor/executor.c executor/executor_utils.c builtins/builtins_utils.c exit_status.c errors.c blt_export_utils.c redirections/redir_heredoc.c redirections/redirs.c message/message.c executor/pipes.c executor/pipes_aux.c executor/executor_aux.c syntax.c redirections/redirs_aux.c executor/executor_utils_2.c free/free.c

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

all:
	@make -C $(LIBFT) > /dev/null
	@make $(NAME)

$(OBJDIR)%.o: %.c
			
			@mkdir -p $(@D)
			@clang $(CFLAGS) $(INCS) -c $< -o $@
			@echo "$(GREEN)[OK]       $(CYAN)Compiled$(ORIGINAL)"

$(NAME): $(OBJECTS) Makefile 
			@mkdir -p $(@D)
			@cc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
			@echo  "$(GREEN)[OK]       $(YELLOW)All Compiled$(ORIGINAL)"

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIBFT) > /dev/null
		@echo  "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

clean:
		@rm -rf $(OBJDIR)
		@rm -f .temp
		@make clean -C $(LIBFT) > /dev/null
		@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

re: fclean all

.PHONY: all clean fclean re
