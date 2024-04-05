/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:13:31 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/03 14:37:21 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(t_token **tokens, char **envp)
{
	t_token	**temp;

	temp = tokens;
	while((*temp))
	{
		if (ft_strcmp((*temp)->wrd, "env"))
			ft_env(envp);
		if (ft_strcmp((*temp)->wrd, "pwd"))
			ft_pwd();
		if (ft_strcmp((*temp)->wrd, "exit"))
			ft_exit(tokens);
		(*temp) = (*temp)->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	const char	*s;
	t_token	**tokens;
	
	tokens = (t_token **)malloc(sizeof(t_token *));
	argv = NULL;
	if (argc != 1)
	{
		perror("Bad args\n");
		exit(0);
	}
	signals();
	while (1)
	{
		s = readline(GREEN "Minishell> " WHITE);
		if (s == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		tokens = get_tok(tokens, (char *)s);
		builtins(tokens, envp);
		ft_expansor(envp, (char *)s);
		ft_quote(s);
		add_history(s);
	}
	return (0);
}
