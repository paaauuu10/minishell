/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/09 14:00:10 by pborrull         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_token		**tokens;
	t_list		**env;
	t_list		**export;

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
	tokens = (t_token **)malloc(sizeof(t_token *));
	if (!tokens)
		exit(1);
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
		ft_executor(tokens, env, export, envp);
		add_history(s);
		free_tokens(tokens);
	}
	return (0);
}
