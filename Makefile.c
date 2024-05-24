# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 13:50:18 by pbotargu          #+#    #+#              #
#    Updated: 2024/05/22 18:23:00 by pbotargu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************** #
#                                          #        
#       	MAKEFILE CASA                  #
#                                          #
# **************************************** #

NAME = minishell

# Colores
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

# Flags de compilación
CFLAGS = -Wall -Wno-unused-variable -Wextra

# Flags del preprocesador
CPPFLAGS = -I./include/ -I./include/Libft $(shell pkg-config --cflags readline)

# Flags del enlazador
LDFLAGS = -L./include/Libft -lft $(shell pkg-config --libs readline)

# Directorios de código fuente y objetos
SRCDIR = src/
OBJDIR = obj/

# Archivos fuente y objetos
SRC_L = blt_cd.c blt_echo.c blt_env.c blt_exit.c blt_export.c blt_pwd.c blt_unset.c expansor.c get_tok.c main.c signals.c utils.c get_list.c quotes.c executor/executor.c executor/executor_utils.c builtins/builtins_utils.c redirections/check_redir.c redirections/redir_utils.c redirections/redirections.c parser/parser.c parser/check.c
SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# Regla principal
all: $(NAME)

# Compilación de archivos objeto
$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(@D)
	@gcc $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "$(GREEN)[OK]       $(CYAN)Compiled $(ORIGINAL)$<"

# Enlace del ejecutable
$(NAME): $(OBJ) $(LIBFT) Makefile
	@gcc $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)
	@echo "$(GREEN)[OK]       $(YELLOW)All Compiled$(ORIGINAL)"

# Ruta a la biblioteca `libft`
LIBFT_DIR = ./include/Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Compilar la biblioteca `libft`
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Limpiar archivos compilados
clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

# Limpiar todo
fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re
