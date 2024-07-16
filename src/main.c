/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/07/16 12:57:16 by pbotargu         ###   ########.fr       */
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
	(void)argv;
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
}

void	ft_free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->wrd);
		free(current);
		current = next;
	}
	free(current);
	head = NULL;
}

static int	ft_main_while(const char *s, t_list **env, t_list **export)
{
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token *));
	if (!tokens)
		exit(1);
	*tokens = NULL;
	s = readline(GREEN "Minishell> " WHITE);
	if (s == NULL)
	{
		printf("exit\n");
		exit(1);
	}
	ft_quote_error(s);
	if (!ft_errors(s))
	{
		tokens = get_tok(env, tokens, (char *)s);
		if (ft_syntax(tokens))
			return (1);
		ft_executor(tokens, env, export);
	}
	add_history(s);
	ft_free_tokens(*tokens);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_list		**env;
	t_list		**export;

	error_checker(argc, argv, envp);
	signals();
	ft_exit_status(0, 1);
	env = env_list(envp);
	if (!env)
		return (1);
	export = env_list(envp);
	if (!export)
	{
		free(env);
		return (1);
	}
	while (1)
		ft_main_while(s, env, export);
	return (0);
}
