/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/13 15:26:58 by pbotargu         ###   ########.fr       */
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
/*************************************************************
			LIBFT BOTA
***************************************************************/
void del(void *content)
{
    free(content);
}

void	ft_lstdelone(t_token *lst, void (*del)(void*))
{
	if (lst)
	{
		(*del)(lst->wrd);
		(*del)(lst->next);
		free(lst);
	}
}


void	ft_lstclear(t_token **lst, void (*del)(void*))
{
	t_token	**l;
	t_token	*next;

	l = lst;
	while (*l)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}




/***********************************************************
			LIBT  BOTA
************************************************************/
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
	*tokens = NULL; //funciona!
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
		if (tokens && *tokens && ft_strcmp((*tokens)->wrd, "exit") == 1)
			ft_exit(tokens);
		ft_executor(tokens, env, export);
//		builtins(tokens, export, env);
	}
	add_history(s);
	//free(*tokens);
	//ft_lstclear(tokens, del);
	//tokens = NULL;
	//free(tokens);
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
	{
		ft_main_while(s, env, export);
	//	free_tokens(tokens);
	}
	return (0);
}
/*
int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_token		**tokens;
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
		if (!ft_errors(s))
		{
			tokens = get_tok(env, tokens, (char *)s);
			if (tokens && *tokens && ft_strcmp((*tokens)->wrd, "exit") == 1)
				ft_exit(tokens);
//			ft_executor(tokens, env, export);
			builtins(tokens, export, env);
		}
		add_history(s);
	//	free_tokens(tokens);
	}
	return (0);
}*/
