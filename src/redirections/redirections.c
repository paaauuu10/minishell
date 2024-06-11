/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:09:41 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/11 12:33:59 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_redirect(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    int i = 0;

    temp = *tokens;
    while (temp)
    {
        if (ft_strcmp(temp->wrd, ">"))
        {
            if (temp->next && temp->next->wrd[0] == '>')
	    	ft_redir_append(tokens, env, export, t_exec);
	    else
	    	ft_redir_out(tokens, env, export, t_exec);
            return (0); //revisar que ha de retornar
        }
        else if (ft_strcmp(temp->wrd, ">>") == 1)
        {
            i = ft_redir_append(tokens, env, export, t_exec);
            return i;
       	}
        else if (ft_strcmp(temp->wrd, "<") == 1)
        {
            //i = ft_redir_in(tokens, env, export, t_exec);
            return i;
        }
        else if (ft_strcmp(temp->wrd, "<<") == 1)
        {
            //i = ft_redir_here(tokens, env, export, t_exec);
            return i;
        }
        temp = temp->next;
    }
    return i;
}
