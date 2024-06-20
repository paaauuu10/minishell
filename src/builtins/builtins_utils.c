/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:47:47 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/14 13:10:22 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_is_builtin(t_token **tokens)
{
    if (!*tokens)
        return (0);
   
    if (ft_strcmp((*tokens)->wrd, "echo") || \
	ft_strcmp((*tokens)->wrd, "env") || \
	ft_strcmp((*tokens)->wrd, "cd") || \
	ft_strcmp((*tokens)->wrd, "pwd") || \
	ft_strcmp((*tokens)->wrd, "exit") || \
	ft_strcmp((*tokens)->wrd, "export") || \
	ft_strcmp((*tokens)->wrd, "unset"))
        return (1);
    return (0);
}   

int	builtins(t_token **tokens, t_list **export, t_list **env)
{
	t_token	**temp;
	int		i;

	i = 0;
	temp = tokens;
	if (*temp)
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
			while ((*temp)->next)
			{
				ft_unset(export, (*temp)->next->wrd);
				ft_unset(env, (*temp)->next->wrd);
				*temp = (*temp)->next;
			}
		}
	}
	return (i);
}
