/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/07/31 16:02:02 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if	(*tokens) 
		ft_free_tokens(*tokens);
	if (tokens)
		free(tokens);
	free((char *)s);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_list		**env;
	t_list		**export;
	char		*a;

	error_checker(argc, argv, envp);
	signals();
	ft_exit_status(0, 1);
	env = env_list(envp);
	if (!env)
		return (1);
	export = env_list(envp);
	if (!export)
	{
		ft_free_env(*env);
		free(env);
		return (1);
	}
	while (1)
		ft_main_while(s, env, export);
	ft_free_env(*env);
	ft_free_env(*export);
	free(env);
	free(export);
	free(a);
	return (0);
}
