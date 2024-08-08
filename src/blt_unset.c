/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:14:15 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/08 13:58:13 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list **export, char *wrd)
{
	t_list	*temp;
	t_list	*prev;
	int		i;

	temp = *export;
	prev = NULL;
	while (temp)
	{
		i = 0;
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
	}
}
