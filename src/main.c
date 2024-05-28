/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
<<<<<<< HEAD:src/main.c
/*   Updated: 2024/05/22 14:16:13 by pborrull         ###   ########.fr       */
=======
/*   Updated: 2024/04/24 14:22:49 by pborrull         ###   ########.fr       */
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:main.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD:src/main.c
void	free_tokens(t_token **tokens)
=======
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
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:main.c
{
	t_token	*temp;

	while (*tokens)
	{
<<<<<<< HEAD:src/main.c
		temp = (*tokens)->next;
		free((*tokens)->wrd);
		free(*tokens);
		*tokens = temp;
=======
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
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:main.c
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
<<<<<<< HEAD:src/main.c
	t_list		**env;
	t_list		**export;

	error_checker(argc, argv, envp);
	//tokens = (t_token **)malloc(sizeof(t_token *));
	//if (!tokens)
	//	exit(1);
	signals();
	ft_exit_status(0, 1);
=======
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
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:main.c
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
<<<<<<< HEAD:src/main.c
		ft_quote_error(s);
		tokens = get_tok(tokens, (char *)s);
		ft_expansor(env, tokens);
		ft_executor(tokens, env, export, envp);
		add_history(s);
	//	free_tokens(tokens);
=======
		ft_quote(s);
		tokens = get_tok(tokens, (char *)s);
		ft_expansor(env, tokens);
		builtins(tokens, export, env);
		add_history(s);
		free_tokens(tokens);
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:main.c
	}
	return (0);
}
