/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/19 14:09:08 by pbotargu         ###   ########.fr       */
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
	t_exec->cmd_count = t_exec->total_pipes + 1;
}

/*---------------------------------------------------------------------------------*/
int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	(void)export;
	t_exec->pid = fork();
	if (t_exec->pid == 0)
	{
		ft_exec(tokens, env, t_exec); //s'ha de modificar
		perror("Command not found");
		exit(127);
	}
	else
		ft_wait_one_child_process();
	return (0); //revisar
}

int	ft_save_fd(t_executor *t_exec)
{
	t_exec->d_pipe->original_stdin = dup(STDIN_FILENO);
	if (t_exec->d_pipe->original_stdin == -1)
	{
		perror("dup");
		return (1);
	}
	t_exec->d_pipe->original_stdout = dup(STDOUT_FILENO);
	if (t_exec->d_pipe->original_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	return (0);
}

void	ft_more_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	(void)env;
	(void)export;
	int	prev_pipefd[2];
	t_exec->d_pipe->pipecounter = 0;
	while (*tokens)
	{
		pipe(t_exec->d_pipe->pipefd);
		t_exec->pid = fork();
		// controlar error pid;
		if (t_exec->pid == 0)
		{
			if (t_exec->d_pipe->pipecounter <= t_exec->total_pipes)
			{
				dup2(t_exec->d_pipe->pipefd[1], 1);
				close(t_exec->d_pipe->pipefd[0]);
				close(t_exec->d_pipe->pipefd[1]);
			}
			if (t_exec->d_pipe->pipecounter != t_exec->total_pipes)
			{
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
		//	ft_send_new_list(tokens, env, export, t_exec); //crear aquesta funcio
		//	ft_only_cmd(tokens, env, export, t_exec);
			exit(1); //revisar exit
		}
		else
		{
	//		ft_wait_one_child();
			if (t_exec->d_pipe->pipecounter <= t_exec->total_pipes)
				close(t_exec->d_pipe->pipefd[1]);
			if (t_exec->d_pipe->pipecounter != t_exec->total_pipes)
			{
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
			prev_pipefd[0] = t_exec->d_pipe->pipefd[0];
			prev_pipefd[1] = t_exec->d_pipe->pipefd[1];
			//ft_wait_one_child();	
			while (*tokens && ((*tokens)->tok != 2))
			{
				printf("Word: %s\n", (*tokens)->wrd);
				printf("Token: %d\n", (*tokens)->tok); // Imprimir el tipo de token para depuración
				(*tokens) = (*tokens)->next;
			}
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
		}
	}
}


/**********************************************************************
				TRYING NEW EXECUTOR
**********************************************************************/
int	ft_executor_2(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (ft_is_builtin(tokens))
		builtins(tokens, env, export);
	(void)t_exec;
	return (0);
	//falten la resta de comandos
}
int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); //revisar
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); //revisar
	if (!tokens || !*tokens)
	{
		free(t_exec);
		return (0);
	}
	ft_exit_status(0, 1);
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	if (t_exec->total_pipes == 0 && !is_redirection(tokens) && ft_is_builtin(tokens))
		builtins(tokens, env, export);
	else if (t_exec->total_pipes == 0 && !is_redirection(tokens))
		ft_only_cmd(tokens, env, export, t_exec);
	else
	{
		ft_pipes(tokens, env, export, t_exec);
		ft_executor_2(tokens, env, export, t_exec);
	}
	free(t_exec->d_pipe);
	free(t_exec);
	return (0);
}

/*void	ft_exec_child(t_executor *t_exec, t_token **tokens, t_list **env, t_list **export)
{
	if (t_exec->pid == 0)
	{
		//TREBALLAR LES PIPES
		//CAL COMPROVAR TOKENS?
		if (ft_is_builtin(tokens))
			exit(builtins(tokens, env, export));
	}
}*/

/*int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); //revisar
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); //revisar
	if (!tokens || !*tokens)
	{
		free(t_exec->d_pipe);
		free(t_exec);
		return (0);
	}
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	pipe(t_exec->d_pipe->pipefd);
	t_exec->pid = fork();
	if (t_exec->pid < 0)
	{
		perror("FORK");
		exit(12);
	}
	ft_exec_child(t_exec, tokens, env, export);
	ft_wait_one_child_process();
	free(t_exec->d_pipe);
	free(t_exec);
	return (0);
}*/

