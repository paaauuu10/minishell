/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:46 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/22 10:38:17 by pbotargu         ###   ########.fr       */
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
int	check_rd(char *str, int i)
{
	if (i <= 0)
		return (1);
	if (!str[i + 1])
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}

int	ft_is_redirection(char *str, int i)
{
	if (i < 2)
		return (0);
	if (!str[i + 1])
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		return (1);
	if (i >= 2 && is_rd(str[i - 1]) && is_rd(str[i - 2]) && is_rd(str[i])) /*falta is_rd*/
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}