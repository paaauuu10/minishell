/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:15:28 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 10:37:01 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_lstnew(char *word, int tokk)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->wrd = word;
	new_node->tok = tokk;
	new_node->next = NULL;
	return (new_node);
}

int	determine_redirection_type(t_token **temp, t_executor *t_exec)
{
	if ((*temp)->tok == 4)
		t_exec->redir_type = REDIR_OUT;
	else
		t_exec->redir_type = REDIR_IN;
	*temp = (*temp)->next;
	if (((*temp)->tok == 4 || (*temp)->tok == 3) && (*temp)->next)
	{
		if ((*temp)->tok == 3)
			t_exec->redir_type = HEREDOC;
		else
			t_exec->redir_type = REDIR_OUT_APPEND;
		*temp = (*temp)->next;
	}
	return (0);
}

void	help_count(t_token **temp, t_executor *t_exec)
{
	while (*temp)
	{
		if ((*temp)->tok == 4 || (*temp)->tok == 3)
		{
			if ((*temp)->tok == 3)
				t_exec->redir_in++;
			else
				t_exec->redir_out++;
			if ((*temp)->next)
			{
				(*temp) = (*temp)->next;
				if (((*temp)->tok == 4 || (*temp)->tok == 3) && (*temp)->next)
					(*temp) = (*temp)->next;
				(*temp) = (*temp)->next;
			}
		}
		else
		{
			t_exec->n_redir++;
			(*temp)->tok = -1;
			(*temp) = (*temp)->next;
		}
	}
}
