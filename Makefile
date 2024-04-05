# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 09:26:08 by pborrull          #+#    #+#              #
#    Updated: 2024/03/20 09:43:33 by pborrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

CFLAGS := -Wall -Werror -Wextra -MMD  -g

SOURCE := main.c signals.c get_tok.c utils.c blt_echo.c blt_env.c blt_pwd.c blt_exit.c expansor.c

LIBFT := libft/

READLINE := readline/

OBJS := $(addprefix ./obj/, $(SOURCE:.c=.o))

DEPS = $(addprefix ./obj/, $(SOURCE:.c=.d))

.SILENT:

all: dir 
	@make -C $(LIBFT) > /dev/null
#	@make -C $(READLINE) > /dev/null
	@make $(NAME)

dir:
	mkdir -p obj > /dev/null

$(NAME): $(OBJS)
	@$(CC)  $(OBJS) -lreadline -L ./libft -lft -o $(NAME)
	@echo  "$(GREEN)[OK]       $(YELLOW)All Compiled$(ORIGINAL)"

./obj/%.o: %.c Makefile
	@$(CC) -c $< -o $@ $(CFLAGS)
	@echo "$(GREEN)[OK]       $(CYAN)Compiled$(ORIGINAL)"

clean:
	@rm -rf obj
	@make clean -C $(LIBFT) > /dev/null
	@make clean -C $(READLINE)
	@rm -f $(OBJS) $(DEPS)
	@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

fclean: clean
	@make fclean -C $(LIBFT) > /dev/null
	@rm -rf $(NAME)
	@echo  "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
