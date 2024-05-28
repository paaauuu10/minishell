/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:22:27 by pborrull          #+#    #+#             */
<<<<<<< HEAD:include/minishell.h
/*   Updated: 2024/05/21 14:30:43 by pborrull         ###   ########.fr       */
=======
/*   Updated: 2024/04/23 15:10:19 by pborrull         ###   ########.fr       */
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:minishell.h
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
<<<<<<< HEAD:include/minishell.h
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
char	*ft_exit_status(int i, int j);

/*----------------------- EXECUTOR ----------------------------*/

int		ft_executor(t_token **tokens, t_list **env,
			t_list **export, char **envp);
int		ft_exec(char *argv, char **envp);
=======
void	signals(void);
int		ft_strcmp(char *s1, char *s2);
char	*ft_str_list(t_token *temp, char *s2);
//char	*ft_str_matrix(char **s1, char *s2);
int		ft_env(t_token **env);
int		ft_echo(t_token **s);
int		ft_quote(const char	*s);
//char	*ft_expansor(char **envp, char *s);//t_token **tokens);
char	*ft_expansor(t_token **env, t_token **tokens);
int		ft_pwd(void);
void	ft_exit(t_token **tokens);
t_token **ft_export(t_token **tokens, t_token **export, t_token **env);
void	ft_unset(t_token	**export, char *wrd);
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:minishell.h

#endif
