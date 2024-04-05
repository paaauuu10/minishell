/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:22:27 by pborrull          #+#    #+#             */
/*   Updated: 2024/03/20 12:21:12 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
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

typedef struct s_token
{
	char			*wrd;
	int				tok;
	struct s_token	*next;
}	t_token;

int		main(int argc, char **argv, char **envp);
t_token	**get_tok(t_token **tokens, char *s);
void	signals(void);
int		ft_strcmp(char *s1, char *s2);
char	*ft_str_matrix(char **s1, char *s2);
int		ft_env(char **env);
int		ft_echo(t_token **s);
int		ft_quote(const char	*s);
char	*ft_expansor(char **envp, char *s);
int		ft_pwd(void);
void	ft_exit(t_token **tokens);

#endif
