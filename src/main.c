/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/16 12:37:16 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**env_list(char **envp)
{
	t_list	**env;
	int		i;

	i = 0;
	env = (t_list **)malloc(sizeof(t_list *));
	if (!env)
		return (NULL);
	while (envp[i])
		add_node(env, new_node(envp[i++]));
/*	while ((*env))
	{
		printf("Title is: %s ", (*env)->title);
		printf("Def is:%s\n", (*env)->def);
		(*env) = (*env)->next;
	}*/
	return (env);
}

int	builtins(t_token **tokens, t_list **export, t_list **env)
{
	t_token	**temp;
	int		i;

	i = 0;
	temp = tokens;
	while ((*temp))
	{
		if (ft_strcmp((*temp)->wrd, "echo"))
		{
			i = ft_echo(tokens);
			return (i);
		}
		if (ft_strcmp((*temp)->wrd, "env"))
			i = ft_env(env);
		if (ft_strcmp((*temp)->wrd, "pwd"))
			i = ft_pwd();
		if (ft_strcmp((*temp)->wrd, "exit"))
			ft_exit(tokens);
		if (ft_strcmp((*temp)->wrd, "export"))
			ft_export(tokens, export, env);
		if (ft_strcmp((*temp)->wrd, "cd"))
			i = ft_cd(tokens, export, env);
		if (ft_strcmp((*temp)->wrd, "unset"))
		{
			ft_unset(export, (*temp)->next->wrd);
			ft_unset(env, (*temp)->next->wrd);
		}
		(*temp) = (*temp)->next;
	}
	return (i);
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->wrd);
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_token		**tokens;
	t_list		**env;
	t_list		**export;

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
		ft_quote_error(s);
		tokens = get_tok(tokens, (char *)s);
		//ft_expansor(env, tokens);
		ft_executor(tokens, env, export);
		//builtins(tokens, export, env);
		add_history(s);
		free_tokens(tokens);
	}
	return (0);
}
