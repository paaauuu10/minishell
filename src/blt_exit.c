/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:11:00 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/23 21:24:15 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token **tokens)
{
	int	n;

	n = 0;
	if ((*tokens)->next && ft_strcmp((*tokens)->next->wrd, "--"))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if ((*tokens)->next && (*tokens)->next->wrd)
		n = ft_atoi((const char *)(*tokens)->next->wrd);
	if ((*tokens)->next && (*tokens)->next->next && n != 255)
	{
		write(2, "Minishell> exit: too many arguments\n", 36);
		ft_exit_status(1, 1);
		return ;
	}
	else if (((*tokens)->next && (*tokens)->next->next) || n == 255)
	{
	//	ft_printf("exit\nMinishell> exit: %s: numeric argument required\n",
	//		(*tokens)->next->wrd);
		write(1, "exit\n", 5);
		if ((*tokens)->next && (*tokens)->next->wrd)
		{
			write(2, "Minishell> exit: ", 17);
			write(2, (*tokens)->next->wrd, ft_strlen((*tokens)->next->wrd));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
	}
	else if ((*tokens) && !(*tokens)->next)
		write(1, "exit\n", 5);
	exit(n);
}
