/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:12 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/22 14:36:19 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_tokens(t_token **s, int i)
{
	t_token	*temp;

	temp = (*s)->next;
	if (i == 1)
		temp = temp->next;
	while (temp)
	{
		printf("%s", temp->wrd);
		temp = temp->next;
		if (temp)
			printf(" ");
	}
	return (0);
}

int	ft_echo(t_token	**s)
{
	if ((*s)->next->wrd[0] == '\0')
		return (ft_printf("\n"));
	if ((*s)->next->wrd[0] == '-' && (*s)->next->wrd[1] == 'n'
		&& !(*s)->next->wrd[2])
	{
		ft_print_tokens(s, 1);
		return (printf("\n"));
	}
	else
	{
		ft_print_tokens(s, 0);
		printf("\n");
		return (0);
	}
}
