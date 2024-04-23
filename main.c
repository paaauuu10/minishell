/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/23 14:46:13 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**env_list(char **envp)
{
	t_token	**env;
	int		i;

	i = 0;
	env = (t_token **)malloc(sizeof(t_token *));
	while (envp[i])
		add_token(env, new_token(envp[i++]));
	return (env);
}

void	builtins(t_token **tokens,t_token **export, t_token **env)
{
	t_token	**temp;

	temp = tokens;
	while ((*temp))
	{
		if (ft_strcmp((*temp)->wrd, "echo"))
		{
			ft_echo(tokens);
			return ;
		}
		if (ft_strcmp((*temp)->wrd, "env"))
			ft_env(env);
		if (ft_strcmp((*temp)->wrd, "pwd"))
			ft_pwd();
		if (ft_strcmp((*temp)->wrd, "exit"))
			ft_exit(tokens);
		if (ft_strcmp((*temp)->wrd, "export"))
			ft_export(tokens, export, env);
		if (ft_strcmp((*temp)->wrd, "unset"))
		{
			ft_unset(export, (*temp)->next->wrd);
			ft_unset(env, (*temp)->next->wrd);
		}
		(*temp) = (*temp)->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_token		**tokens;
	t_token		**env;
	t_token		**export;
	
	tokens = (t_token **)malloc(sizeof(t_token *));
	argv = NULL;
	if (argc != 1)
	{
		perror("Bad args\n");
		exit(0);
	}
	signals();
	env = env_list(envp);
	export = env_list(envp);
	while (1)
	{
		s = readline(GREEN "Minishell> " WHITE);
		if (s == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		tokens = get_tok(tokens, (char *)s);
		builtins(tokens, export, env);
		ft_expansor(envp, (char *)s);
		ft_quote(s);
		add_history(s);
	}
	return (0);
}
