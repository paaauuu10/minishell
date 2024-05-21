/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:11:00 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/21 12:02:49 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	ft_exit(t_token **tokens)
{
	int	n;

	n = 0;
	if ((*tokens)->next && ft_strcmp((*tokens)->next->wrd, "--"))
	{
		ft_printf("exit\n");
		exit(0);
	}
	if ((*tokens)->next && (*tokens)->next->wrd)
		n = ft_atoi((const char *)(*tokens)->next->wrd);
	if ((*tokens)->next && (*tokens)->next->next && n != 255)
	{
		ft_printf("Minishell> exit: too many arguments\n");
		return ;
	}
	else if (((*tokens)->next && (*tokens)->next->next) || n == 255)
	{
		ft_printf("exit\nMinishell> exit: %s: numeric argument required\n",
			(*tokens)->next->wrd);
		exit(255);
	}
	else if ((*tokens) && !(*tokens)->next)
		ft_printf("exit\n");
	exit(n);
}
