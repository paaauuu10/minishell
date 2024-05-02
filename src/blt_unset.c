/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/30 14:45:23 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(t_token	**export, char *wrd)
{
	t_token	*temp;
	t_token	*prev;
	int		i;

	i = 0;
	temp = *export;
	while (temp)
	{
		while (temp->wrd[i] && wrd[i] && temp->wrd[i] == wrd[i])
			i++;
		if (!wrd[i] && (temp->wrd[i] == '=' || !temp->wrd[i]))
		{
			prev->next = temp->next;
			return ;
		}
		prev = temp;
		temp = temp->next;
		i = 0;
	}
}
