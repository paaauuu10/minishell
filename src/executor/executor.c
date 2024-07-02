/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/02 10:24:31 by pbotargu         ###   ########.fr       */
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
	t_exec->d_pipe->pipecounter = t_exec->total_pipes;
	t_exec->cmd_count = t_exec->total_pipes + 1;
}

/*---------------------------------------------------------------------------------*/
int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	char	*aux;

	aux = (*tokens)->wrd;
	(void)export;
	t_exec->pid = fork();
	if (t_exec->pid == 0)
	{
		ft_exec(tokens, env, t_exec); //s'ha de modificar
		ft_print_error(aux);
		write(2, ": command not found\n", 20);
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

/**********************************************************************
				TRYING NEW EXECUTOR
**********************************************************************/
int	ft_executor_2(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (ft_is_builtin(tokens))
		builtins(tokens, env, export);
	else
		ft_only_cmd(tokens, env, export, t_exec);
	return (0);
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
		//ft_redirs(tokens, env, export, t_exec);
		//ft_pipes(tokens, env, export, t_exec);
		ft_redirs(tokens, env, export, t_exec);
	}
	free(t_exec->d_pipe);
	free(t_exec);
	return (0);
}
