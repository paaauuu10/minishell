NAME = minishell
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

INCS = -I./include/ -I./include/Libft -I$(HOME)/.brew/opt/readline/include
LIBFTA = -L./include/Libft -lft
READLINE = -L$(HOME)/.brew/opt/readline/lib -lreadline
SRCDIR = src/
OBJDIR = obj/

SRC_L = blt_echo.c blt_env.c blt_exit.c blt_export.c blt_pwd.c blt_unset.c expansor.c get_tok.c main.c signals.c utils.c

SRC = $(addprefix $(SRCDIR), $(SRC_L))
OBJECTS = $(addprefix $(OBJDIR), $(SRC:.c=.o))

#OLD_MAKE = /usr/bin/make3.81 #make

all: $(NAME)

$(OBJDIR)%.o: %.c
			@printf "Compiling objects\n"
			@mkdir -p $(@D)
			@gcc $(CFLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJECTS) Makefile include/minishell.h 
			@mkdir -p $(@D)
			@gcc $(CFLAGS) -o $@ $(OBJECTS) $(LIBFTA) $(READLINE)
			@printf "\nCompiled successfully!\n"

fclean: clean
		@rm -rf $(NAME)

clean:
		@rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
