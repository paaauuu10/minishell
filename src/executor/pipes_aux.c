/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:38:07 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/02 10:39:50 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_aux_lst(t_token **tokens, t_token *aux_head)
{
	//t_token	*aux;

	//aux = *tokens;
	aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
		{
			add_token(&aux_head, new_token((*tokens)->wrd, (*tokens)->hd_nbr));
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			else
				break ;
		}
	}
	//*tokens = aux;
	return (aux_head);
}
