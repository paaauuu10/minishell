/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:09:41 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/15 14:33:49 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_redirect(t_token **tokens, t_executor *t_exec)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, ">"))
		{
			if (temp->next && temp->next->wrd[0] == '>')
				return (t_exec->redir_type = REDIR_OUT_APPEND);
			else
				return (t_exec->redir_type = REDIR_OUT);
		}
		else if (ft_strcmp(temp->wrd, "<") == 1)
		{
			if (temp->next && temp->next->wrd[0] == '<')
				return (t_exec->redir_type = HEREDOC);
			else
				return (t_exec->redir_type = REDIR_IN);
		}
		temp = temp->next;
	}
	return (0);
}
