/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:31:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/06 11:24:47 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_wait_one_child_process()
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

void	ft_wait_childs_process(int	*exit_status, int i, t_executor *t_exec)
{
	int j;
	int status;
	
	j = 0;
	while (j > i)
	{
		if (t_exec->pid == wait(&status))
		{
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					*exit_status = 130;
				else if (WTERMSIG(status) == SIGQUIT)
				{
					printf("Quit: 3\n");
					*exit_status = 131;
				}
			}
		}
		j++;
	}
}
