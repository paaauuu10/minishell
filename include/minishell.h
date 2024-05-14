/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:22:27 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/14 09:13:14 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "readline/history.h"
# include "libft/libft.h"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1b[0m"

typedef struct s_list
{
	char			*title;
	char			*def;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char			*wrd;
	int				tok;
	struct s_token	*next;
}	t_token;

typedef struct s_executor
{
	int	pid;
	int	total_pipes;
	int	exit_status;
}	t_executor;

/*---------------------- BUILTINGS ----------------------------*/

int		builtins(t_token **tokens, t_list **export, t_list **env);
int		ft_pwd(void);
int		ft_cd(t_token	**tokens, t_list **export, t_list	**env);
void	ft_exit(t_token **tokens);
int		ft_echo(t_token **s);
t_list	**ft_export(t_token **tokens, t_list **export, t_list **env);
void	ft_unset(t_list **export, char *wrd);
int		ft_env(t_list **env);
int		ft_is_builtin(t_token **tokens);

/*------------------------ LIST -------------------------------*/

t_token	**get_tok(t_token **tokens, char *s);
void	add_token(t_token **tokens, t_token	*node);
t_token	*new_token(char *s);
int		change_tok(t_token **export, char *new_wrd);
char	*ft_str_list(t_list **temp, char *s2);
t_list	*new_node(char *s);
t_list	**env_list(char **envp);
char	*ft_title(char *s);
char	*ft_def(char *s);
void	add_node(t_list **env, t_list *node);

/*------------------------ OTHER ------------------------------*/

void	signals(void);
int		ft_strcmp(char *s1, char *s2);
char	**ft_quotes(const char *s);
int		ft_quote_error(const char *s);
char	*ft_expansor(t_list **env, t_token **tokens);
char	*ft_strcat(char *temp_wrd, char *exp, int i);

/*----------------------- EXECUTOR ----------------------------*/

int		ft_executor(t_token **tokens, t_list **env,
			t_list **export, char **envp);
int		ft_exec(char *argv, char **envp);

#endif
