/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:46 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/18 13:04:55 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirection(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
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

void	ft_count_redirects(t_token **tokens, t_executor *t_exec)
{
	t_token	*temp;

	temp = (*tokens);
	t_exec->redir_out = 0;
	t_exec->redir_in = 0;
	while (temp->next)
	{
		if (temp->tok == 4 || temp->tok == 3)
		{
			if (temp->tok == 3)
			{
				t_exec->redir_in++;
				t_exec->flag_red = LAST_GLB_IN;
			}
			else
			{
				t_exec->flag_red = LAST_GLB_OUT;
				t_exec->redir_out++;
			}
			if (temp->next)
			{
				temp = temp->next;
				if ((temp->tok == 4 || temp->tok == 3) && temp->next)
					temp = temp->next;
			}
		}
		if (temp->next)
			temp = temp->next;
	}
	if (t_exec->redir_out > 0 && t_exec->redir_in > 0)
	{
		ft_find_last_in(tokens, t_exec);
		ft_find_last_out(tokens, t_exec);
	}
}
