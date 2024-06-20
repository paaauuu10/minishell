/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:09:41 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/20 14:11:18 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_redirect(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	t_token	*temp;
	char	*filename;
	
	(void)env;
	(void)export;
	temp = *tokens;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, ">"))
		{
			if (temp->next && temp->next->wrd[0] == '>')
			{	
				t_exec->redir_type = REDIR_OUT_APPEND;
				return (REDIR_OUT_APPEND);
			}
			else
			{
				t_exec->redir_type = REDIR_OUT;
				return (REDIR_OUT);
			}
			return (0); //revisar que ha de retornar
		}
		else if (ft_strcmp(temp->wrd, "<") == 1)
		{
			if (temp->next && temp->next->wrd[0] == '<')
				ft_redir_here(tokens);
			else
			{
				filename = (*tokens)->next->next->wrd;
				ft_redir_in(filename, t_exec);
			}
			return (0); //revisar que ha de retornar
		}
		temp = temp->next;
	}
	return (0);
}
