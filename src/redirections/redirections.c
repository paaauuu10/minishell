/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:46 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/17 12:28:50 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     is_redirection(t_token **tokens)
{
    t_token *temp;

    temp = *tokens;
    while(temp)
    {
        if (ft_strcmp(temp->wrd, ">") || \
        ft_strcmp(temp->wrd, "<") || \
        ft_strcmp(temp->wrd, ">>") || \
        ft_strcmp(temp->wrd, "<<"))
            return (1);
        temp = temp->next;
    }
    return (0);
}