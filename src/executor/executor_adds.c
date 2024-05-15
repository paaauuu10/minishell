/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_adds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:04:03 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/15 11:49:59 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_is_redirection(t_token **tokens)
{
    t_token *temp;

    temp = *tokens;
    if (!*tokens || !tokens)
        return (0);
    while(temp)
    {
        if (ft_strcmp((temp)->wrd, ">") || \
        ft_strcmp((temp)->wrd, "<") || \
        ft_strcmp((temp)->wrd, "<<") || \
        ft_strcmp((temp)->wrd, ">>"))
        {
            printf("FOUNND ft_is\n");
            return (1);
        }
        temp = temp->next;
    }
    return (0);
}
/*int	ft_is_builtin(t_token **tokens)
{
	if (!*tokens)
		return (0);
	if (ft_strcmp((*tokens)->wrd, "echo") || \
	ft_strcmp((*tokens)->wrd, "env") || \
	ft_strcmp((*tokens)->wrd, "pwd") || \
	ft_strcmp((*tokens)->wrd, "exit") || \
	ft_strcmp((*tokens)->wrd, "cd") || \
	ft_strcmp((*tokens)->wrd, "export") || \
	ft_strcmp((*tokens)->wrd, "unset"))
		return (1);
	return (0);
}*/

