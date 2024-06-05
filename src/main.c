/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/05 14:11:25 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	error_checker(int argc, char **argv, char **envp)
{
	if (!*envp)
	{
		printf("Minishell need the envp to work.\n");
		exit(1);
	}
	if (argc != 1)
	{
		printf("Minishell only need minishell, no more.\n");
		exit(1);
	}	
	argv = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_token		**tokens;
	t_list		**env;
	t_list		**export;
	error_checker(argc, argv, envp);
	//tokens = (t_token **)malloc(sizeof(t_token *));
	//if (!tokens)
	//	exit(1);
	signals();
	ft_exit_status(0, 1);
	env = env_list(envp);
	export = env_list(envp);
	while (1)
	{
		tokens = (t_token **)malloc(sizeof(t_token *));
		if (!tokens)
			exit(1);
		s = readline(GREEN "Minishell> " WHITE);
		if (s == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		ft_quote_error(s);
		tokens = get_tok(tokens, (char *)s);
		if (ft_strcmp((*tokens)->wrd, "exit") == 1)
			ft_exit(tokens);
		ft_expansor(env, tokens);
		printf("1\n");
		ft_executor(tokens, env, export); //pasarli el envp original per a provar execve
		printf("2\n");
		add_history(s);
	//	free_tokens(tokens);
	}
	return (0);
}
