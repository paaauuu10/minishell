/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:31:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/24 11:34:40 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_wait_one_child_process(int *exit_status)
{
	int	status;

	wait(&status);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
	    if (WTERMSIG(status) == SIGINT)
	    {
		    *exit_status = 130;
		    write(1, "\n", 1);
	    }
	    else if (WTERMSIG(status) == SIGQUIT)
	    {
	    	*exit_status = 131;
	    	ft_putstr_fd("Quit: 3\n", 1);
	    }
    }
}