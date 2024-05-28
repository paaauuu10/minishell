/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:12 by pborrull          #+#    #+#             */
<<<<<<< HEAD:src/blt_echo.c
/*   Updated: 2024/05/21 15:22:03 by pborrull         ###   ########.fr       */
=======
/*   Updated: 2024/04/18 15:39:47 by pborrull         ###   ########.fr       */
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:blt_echo.c
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
<<<<<<< HEAD:src/blt_echo.c
	if (!(*s))
		return (0);
	if ((*s)->next && (*s)->next->wrd[0] == '\0')
		return (ft_printf("\n"));
	if ((*s)->next && (*s)->next->wrd[0] == '-' && (*s)->next->wrd[1] == 'n'
		&& !(*s)->next->wrd[2])
	{
		ft_print_tokens(s, 1);
		return (0);
=======
	if ((*s)->next->wrd[0] == '\0')
		return (ft_printf("\n"));
	if ((*s)->next->wrd[0] == '-' && (*s)->next->wrd[1] == 'n' && !(*s)->next->wrd[2])
	{
		ft_print_tokens(s, 1);
		return (printf("\n"));
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:blt_echo.c
	}
	else
	{
		ft_print_tokens(s, 0);
		printf("\n");
<<<<<<< HEAD:src/blt_echo.c
=======
	//	return (ft_print_tokens(s, 0));
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:blt_echo.c
		return (0);
	}
}
