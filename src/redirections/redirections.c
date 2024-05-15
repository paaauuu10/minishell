/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:31:00 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/15 12:36:29 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     redirections(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    
    temp == *tokens;
    while(temp)
    {
        if (ft_strcmp(temp->wrd, ">"))
            ft_output_redirect(tokens, t_exec);
        if (ft_strcmp(temp->wrd, "<"))
            return (0);
        if (ft_strcmp(temp->wrd, ">>"))
            return(0);
        if (ft_strcmp(temp->wrd, "<<"))
            return (0);
        temp = temp->next;
    }
    return (0);
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