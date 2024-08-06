/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:14:15 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/06 14:35:31 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	ft_unset_aux(t_list **export, t_list *temp, char *wrd, int i)
{
	if (!wrd[i] && !temp->title[i])
	{
		*export = temp->next;
		free(temp->title);
		free(temp);
		return (1);
	}
	return (0);
}*/

void	ft_unset(t_list **export, char *wrd)
{
	t_list	*temp;
	t_list	*prev;
	int		i;

	i = 0;
	temp = *export;
	prev = NULL;
	while (temp)
	{
		while (temp->title[i] && wrd[i] && temp->title[i] == wrd[i])
			i++;
		if (!wrd[i] && !temp->title[i])
		{
			if (prev == NULL)
				*export = temp->next;
			else
				prev->next = temp->next;
			free(temp->title);
			free(temp->def);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
		i = 0;
	}
}
