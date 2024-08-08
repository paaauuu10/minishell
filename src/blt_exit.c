/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:11:00 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/08 12:58:36 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cond(t_token **tokens)
{
	write(1, "exit\n", 5);
	if ((*tokens)->next && (*tokens)->next->wrd)
	{
		write(2, "Minishell> exit: ", 17);
		write(2, (*tokens)->next->wrd, ft_strlen((*tokens)->next->wrd));
		write(2, ": numeric argument required\n", 28);
		ft_exit_status(2, 1);
		exit(2);
	}
}

void	ft_exit(t_token **tokens, t_list **env, t_list **export)
{
	int	n;

	n = ft_exit_status(0, 0);
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
	else if ((*tokens)->next && n == 255)
		cond(tokens);
	(void)export;
	(void)env;
	write(1, "exit\n", 5);
	exit(n);
}
