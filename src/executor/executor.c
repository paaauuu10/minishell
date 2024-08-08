/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 09:06:15 by pbotargu         ###   ########.fr       */
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
		if (temp->tok == 2)
			t_exec->total_pipes++;
		temp = temp->next;
	}
	t_exec->d_pipe->pipecounter = t_exec->total_pipes;
	t_exec->cmd_count = t_exec->total_pipes + 1;
}

int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	t_token	*aux;

	aux = *tokens;
	(void)export;
	if ((*tokens)->tok > 0)
		return (1);
	t_exec->pid = fork();
	if (t_exec->pid == 0)
	{
		signals();
		if ((*tokens)->wrd[0] == '/' || (*tokens)->wrd[0] == '.')
			ft_exec_absolut(tokens, t_exec);
		else
			ft_exec(tokens, env, t_exec);
		ft_print_error(aux->wrd);
		*tokens = aux;
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else
		ft_wait_one_child_process();
	return (0);
}

/**********************************************************************
				TRYING NEW EXECUTOR
**********************************************************************/
int	ft_executor_2(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	if (ft_is_builtin(tokens))
		builtins(tokens, env, export);
	else
		ft_only_cmd(tokens, env, export, t_exec);
	return (0);
}

void	ft_free_mini(t_executor *t_exec)
{
	int	i;

	i = 0;
	ft_reset_fd(t_exec);
	free(t_exec->d_pipe);
	while (t_exec->new_envp[i])
		free(t_exec->new_envp[i++]);
	free(t_exec->new_envp);
	free(t_exec);
}

int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_list		*temp;

	temp = *env;
	*env = temp;
	if (!tokens || !*tokens)
		exit(1);
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1);
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1);
	set_exec(tokens, env, t_exec);
	if ((*tokens)->wrd[0] == '$' && (*tokens)->wrd[1])
	{
		ft_free_mini(t_exec);
		return (1);
	}
	run_exec(tokens, env, export, t_exec);
	ft_reset_fd(t_exec);
	ft_free_mini(t_exec);
	return (0);
}
