/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:35:47 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/31 12:58:38 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->title)
			free(tmp->title);
		if (tmp->def)
			free(tmp->def);
		free(tmp);
	}
}

/*void	ft_free_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		if (temp->wrd)
			free(temp->wrd);
		temp = NULL;
		free(temp);
	}
}*/

void	ft_free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->wrd);
		free(current);
		current = NULL;
		current = next;
	}
	free(current);
	head = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->wrd);
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}
