/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/16 18:34:52 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_count_pipes(t_executor *t_exec, t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	t_exec->total_pipes = 0;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, "|"))
			t_exec->total_pipes++;
		temp = temp->next;
	}
}
/*void ft_child_process(t_executor *t_exec, t_token **tokens)
{
	char **argv;
	argv[0] = "ls";
	argv[1] = NULL;
	//SI ES UNA PIPE 
		//dup2(pipefd[1], 1);
		//close(pipefd[1]);
		//close(pipefd[0]);
	execve("/bin/ls", argv, NULL);
	exit(1);
}*/
void	ft_child_process(t_executor *t_exec, t_token **tokens, t_list *env, t_list *export)
{
	if (ft_is_builtin(tokens))
		exit(builtins(tokens, export, env));
	else
		ft_exec_cmd(t_exec);
}
void	ft_fork(t_token *tokens, t_executor *t_exec, t_list *env, t_list *export)
{
	int	pid;
	pid = fork();
	if (pid < 0)
		perror("PID ERROR\n");
	if (pid == 0)
		ft_child_process(t_exec, tokens, env, export);
	else
	{	
		ft_wait(t_exec, pid, t_exec->ret_val);
		usleep(50000);
	}
	// close fds function
}
void	ft_init_fd(t_executor *t_exec)
{
	t_exec->pipe_fd[IN] = -1;
	t_exec->pipe_fd[OUT] = -1;
	t_exec->prev_pipe[IN] = -1;
	t_exec->prev_pipe[OUT] = -1;
	t_exec->fd_init[IN] = dup(STDIN_FILENO);
	t_exec->fd_init[OUT] = dup(STDOUT_FILENO);
	t_exec->redirection[IN] = 0;
	t_exec->redirection[OUT] = 0;
	t_exec->ret_val = 0;
}
int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	pid_t	pid;
	t_executor	*t_exec;
	//int status;
	//int pipfd[2]
	t_exec = malloc(sizeof(t_executor));
	ft_memset(t_exec, 0, sizeof(t_executor));
	if (!tokens || !*tokens)
	{
		free(t_exec);
		return (0);
	}
	
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	t_exec->pid = fork();
	if (t_exec->pid < 0)
		return (0); revisar com tractem l'error 
	//ft_child(t_exec, tokens, env);
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	ft_init_fd(t_exec);
	ft_fork(tokens, t_exec, env, export);
	
	
	










	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	 
	
	ft_count_pipes(t_exec, tokens);
	if (ft_is_builtin(tokens) == 1 && t_exec->total_pipes == 0)
	{
		t_exec->exit_status = builtins(tokens, export, env);
		return (1); //revisar
	}
	else if (t_exec->total_pipes == 0) //revisar condicions 
	{
		t_exec->pid = fork();
		if (t_exec->pid < 0)
		{
			printf("pid < 0");
			return (0); //revisar
		}
		if (t_exec->pid == 0)
			ft_exec(tokens, env, t_exec); //s'ha de modificar
		else
			waitpid(t_exec->pid, 0, 0); //aixo sha de revisar
	}
	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	






	/* t_exec->pid = fork();
	if (t_exec->pid < 0)
		return (1);
	if (t_exec->pid == 0)
		ft_child_process(t_exec, tokens);
	wait(&status);
	//SI ES UNA PIPE 
		//dup2(pipefd[0], 0);
		//close(pipefd[1]);
		//close(pipefd[0]);
	free(t_exec);*/
	return (0);
}
