/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:31:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/05 12:20:37 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ft_wait_one_child_process(int *exit_status)
{
	printf("1.2.2.1\n");
	int	status;

	wait(&status);
	printf("1.2.2.2\n");
	if (WIFEXITED(status))
	{
		printf("1.2.2.3\n");
		*exit_status = WEXITSTATUS(status);
		printf("1.2.2.4\n");
	}
	else if (WIFSIGNALED(status))
	{
	    printf("1.2.2.5\n");
	    if (WTERMSIG(status) == SIGINT)
	    {
		    printf("1.2.2.6\n");
		    *exit_status = 130;
		    printf("1.2.2.7\n");
	    }
	    else if (WTERMSIG(status) == SIGQUIT)
	    {
	    	printf("1.2.2.8\n");
		*exit_status = 131;
		printf("1.2.2.9\n");
	    	ft_putstr_fd("Quit: 3\n", 1);
	    	printf("1.2.2.10\n");
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
