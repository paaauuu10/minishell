/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/09 13:48:23 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_list **export, char *wrd)
{
	t_list	*temp;
	t_list	*prev;
	int		i;

	i = 0;
	temp = *export;
	while (temp->title[i] && wrd[i] && temp->title[i] == wrd[i])
		i++;
	if (!wrd[i] && !temp->title[i])
	{
		*export = temp->next;
		return ;
	}
	while (temp)
	{
		while (temp->title[i] && wrd[i] && temp->title[i] == wrd[i])
			i++;
		if (!wrd[i] && !temp->title[i])
		{
			prev->next = temp->next;
			return ;
		}
		prev = temp;
		temp = temp->next;
		i = 0;
	}
}
