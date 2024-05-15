/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:31:00 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/15 12:37:13 by pbotargu         ###   ########.fr       */
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