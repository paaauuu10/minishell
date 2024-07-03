/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:31:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/03 14:40:10 by pbotargu         ###   ########.fr       */
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

// Función para esperar a todos los procesos hijos
void ft_wait_childs_process(int num_children, t_executor *t_exec)
{
    int status;
    int exit_status;

    for (int j = 0; j < num_children; j++)
    {
        pid_t pid = wait(&status); // Espera a cualquier proceso hijo

        if (pid == -1)
        {
            perror("wait");
            return;
        }

        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
            ft_exit_status(exit_status, 1);
            //printf("Child %d exited with status %d\n", pid, exit_status);
        }
        else if (WIFSIGNALED(status))
        {
            int term_signal = WTERMSIG(status);
            if (term_signal == SIGINT)
            {
                ft_exit_status(130, 1);
                //printf("Child %d terminated by SIGINT\n", pid);
            }
            else if (term_signal == SIGQUIT)
            {
                ft_exit_status(131, 1);
                //printf("Child %d terminated by SIGQUIT (Quit: 3)\n", pid);
            }
            else
            {
                ft_exit_status(128 + term_signal, 1);
                //printf("Child %d terminated by signal %d\n", pid, term_signal);
            }
        }
    }
	(void)t_exec;
}


/*void	ft_wait_childs_process(int i, t_executor *t_exec)
{
	int		j;
	int		status;
	int		k;

	k = 0;
	j = 0;
	while (j < i)
	{
		if (t_exec->pid == wait(&status))
		{
			if (WIFEXITED(status))
			{
				k = WEXITSTATUS(status);
				ft_exit_status(k, 1);
				printf(" K: %d\n", k);
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
}*/
