/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:31:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/21 10:09:57 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_wait_one_child_process(void)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
	{
		ft_exit_status(WEXITSTATUS(status), 1);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_exit_status(130, 1);
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_exit_status(131, 1);
			ft_putstr_fd("Quit: 3\n", 1);
		}
	}
}

void	ft_wait_childs_process(int i, t_executor *t_exec)
{
	int		j;
	int		status;
	int		k;

	k = 0;
	j = 0;
	while (j > i)
	{
		if (t_exec->pid == wait(&status))
		{
			if (WIFEXITED(status))
			{
				k = WEXITSTATUS(status);
				ft_exit_status(k, 1);
			}
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					ft_exit_status(130, 1);
				else if (WTERMSIG(status) == SIGQUIT)
				{
					printf("Quit: 3\n");
					ft_exit_status(131, 1);
				}
			}
		}
		j++;
	}
}
