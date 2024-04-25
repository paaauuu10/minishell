/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/18 14:50:54 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
