/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/24 12:38:54 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_count_pipes(t_executor *t_exec, t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	t_exec->total_pipes = 0;
	t_exec->d_pipe->flag = INACTIVE;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, "|"))
		{
			t_exec->total_pipes++;
			t_exec->d_pipe->flag = ACTIVE;
		}
		temp = temp->next;
	}
	t_exec->d_pipe->pipecounter = t_exec->total_pipes;
}

int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (ft_is_builtin(tokens))
	{
		t_exec->exit_status = builtins(tokens, export, env);
		return (1); //revisar
	}
	t_exec->pid = fork();
	if (t_exec->pid < 0)
	{
		printf("pid < 0");
		return (0);   //revisar
	}
	if (t_exec->pid == 0)
	{
		ft_exec(tokens, env, t_exec); //s'ha de modificar
		//perror("Comand not found");
		//if (kill(t_exec->pid, SIGTERM) == -1)
		//	perror("KILL");
	}
	else
		ft_wait_one_child_process(&t_exec->exit_status); //aixo sha de revisar
	return (0); /*revisar*/
}
int	ft_save_fd(t_executor *t_exec)
{
	t_exec->d_pipe->original_stdin = dup(STDIN_FILENO);
	if (t_exec->d_pipe->original_stdin == -1)
	{
		perror("dup");
		return (1);
	}
	t_exec->d_pipe->original_stdin = dup(STDOUT_FILENO);
	if (t_exec->d_pipe->original_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	return (0);
}

void	ft_more_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (&is_redirection && t_exec->total_pipes == 0)
		ft_redirect(tokens, env, export, t_exec);
	else
	{
		t_exec->pid = fork();
		if (t_exec->pid < 0)
		{
			perror ("pid"); /*revisar*/
			exit (1); /*revisar*/
		}
		if (t_exec->pid == 0)
		{
		/*if (t_exec->d_pipe->flag == ACTIVE)
		{
			ft_dub2(t_exec->d_pipe->pipefd[1], 1);
			ft_close2(t_exec->d_pipe->pipefd[1], t_exec->d_pipe->pipefd[0]);
		}*/
			if (!tokens || !*tokens)
				exit (0); /*revisar*/
			if (ft_is_builtin(tokens))
				exit(builtins(tokens, export, env));
			else
				ft_exec(tokens, env, t_exec);
			if (t_exec->pid == 0)
				kill(t_exec->pid, SIGTERM);
		}
		else
			ft_wait_one_child_process(&t_exec->exit_status);
	}
}
int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); /*revisar*/
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); /*revisar*/
	t_exec->d_pipe->flag = INACTIVE;
	if (!tokens || !*tokens)
	{
		free(t_exec);
		return (0);
	}
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	if (!is_redirection(tokens) && t_exec->total_pipes == 0)
	{
		printf("1\n");
		ft_only_cmd(tokens, env, export, t_exec);
	}
	else
	{
		printf("2\n");
		ft_more_cmd(tokens, env, export, t_exec);
	}
	printf("3\n");
	free(t_exec->d_pipe);
	free(t_exec);
	return (0);
}
