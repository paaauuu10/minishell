/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:31:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 11:43:13 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ignore_signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		perror("Error ignoring SIGINT");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Error ignoring SIGQUIT");
		exit(EXIT_FAILURE);
	}
}

void	ft_wait_one_child_process(void)
{
	int	status;

	ignore_signals();
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
	signals();
}

void	ft_aux_wait(int status)
{
	int	term_signal;

	term_signal = WTERMSIG(status);
	if (term_signal == SIGINT)
		ft_exit_status(130, 1);
	else if (term_signal == SIGQUIT)
		ft_exit_status(131, 1);
	else
		ft_exit_status(128 + term_signal, 1);
}

void	ft_wait_childs_process(int num_children, t_executor *t_exec)
{
	int		status;
	pid_t	pid;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (j < num_children)
	{
		pid = wait(&status);
		if (pid == -1)
		{
			perror("wait");
			return ;
		}
		if (WIFEXITED(status))
			k = ft_exit_status(WEXITSTATUS(status), 1);
		else if (WIFSIGNALED(status))
			ft_aux_wait(status);
		j++;
	}
	(void)t_exec;
}
