/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:22:27 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/26 12:50:11 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	int				stop_flag;
	struct s_token	*next;
}	t_token;

typedef struct s_pipe
{
	int	pipefd[2];
	int	pipecounter;
	int	flag;
	int	original_stdin;
	int	original_stdout;
}	t_pipe;

typedef struct s_executor
{
	int		pid;
	int		redir_type;
	int		total_pipes;
	int		cmd_count;
	int		exit_status;
	char	*absolute_path;
	char	**path;
	char	**new_envp;
	char	*cmd;
	char	**cmd_argv;
	t_list	*env;
	t_list	*exp;
	t_pipe	*d_pipe;
}	t_executor;

typedef struct s_parser
{
	int		i;
	int		j;
	int		k;
	char	quote;
	int		count;
	int		open;
}	t_parser;

# define IN 0
# define OUT 1

# define REDIR_OUT 10
# define REDIR_OUT_APPEND 11
# define REDIR_IN 12
# define HEREDOC 13

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

t_token	**get_tok(t_list **env, t_token **tokens, char *s);
void	add_token(t_token **tokens, t_token	*node);
t_token	*new_token(char *s);
int		change_tok(t_token **export, char *new_wrd);
char	*ft_str_list(t_list **temp, char *s2);
t_list	*new_node(char *s);
t_list	**env_list(char **envp);
char	*ft_title(char *s);
char	*ft_def(char *s);
void	add_node(t_list **env, t_list *node);
void	put_exp(t_list **export, char *wrd);
void	put_env(t_list **env, char *wrd);

/*------------------------ OTHER ------------------------------*/

void	signals(void);
int		ft_strcmp(char *s1, char *s2);
char	**ft_quotes(const char *s, t_list **env);
int		ft_quote_error(const char *s);
char	*ft_expansor(t_list **env, char *s);
char	*ft_strcat(char *temp_wrd, char *exp, int i);
char	*ft_exit_status(int i, int j);
int		ft_errors(const char *s);

/*----------------------- EXECUTOR ----------------------------*/

int		ft_executor(t_token **tokens, t_list **env, t_list **export);
int		ft_exec(t_token **tokens, t_list **env, t_executor *t_exec);
int		ft_only_cmd(t_token **tokens, t_list **env,
			t_list **export, t_executor *t_exec);
int		ft_pipes(t_token **tokens, t_list **env, 
			t_list **export, t_executor *t_exec);
int	ft_executor_2(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec);

/*----------------------- REDIRECTIONS ------------------------*/

int		is_redirection(t_token **tokens);
int		ft_is_redirection(char *str, int i);
int		check_rd(char *str, int i);
int		ft_redirect(t_token **tokens, t_list **env,
			t_list **export, t_executor *t_exec);
int		ft_redir_out(t_token **tokens, t_list **env,
			t_list **export, t_executor *t_exec);
int		ft_redir_in(char *filename, t_executor *t_exec);
int		ft_redir_append(t_token **tokens, t_list **env,
			t_list **export, t_executor *t_exec);
int		ft_redir_here(t_token **tokens);
int		ft_redirs(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec);

t_token	*ft_lstnew(char *word, int tokk);

/*------------------------ WAIT --------------------------------*/

void	ft_wait_one_child_process(void);
void	ft_wait_childs_process(int i, t_executor *t_exec);

/*------------------------ MESSAGE -----------------------------*/

void	ft_print_error(char *a);

#endif
