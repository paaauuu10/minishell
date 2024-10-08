/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:16:25 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/07 15:50:20 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_pipe(t_token **tokens)
{
	while ((*tokens) && (*tokens)->tok != 2)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		else
			break ;
	}
	if ((*tokens) && (*tokens)->tok == 2)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
	}
}

void	ft_cmd_exec(t_token **tokens, t_list **env, t_list **export, \
		t_executor *t_exec)
{
	if (ft_redirect(tokens, t_exec) != 0)
		exit(ft_redirs(tokens, env, export, t_exec));
	else if (ft_is_builtin(tokens))
		exit(builtins(tokens, env, export));
	else
	{
		ft_exec(tokens, env, t_exec);
		perror("execvp");
	}
	exit(EXIT_FAILURE);
}

void	ft_parent(t_data *data, t_token **tokens, t_executor *t_exec)
{
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (data->i < t_exec->cmd_count - 1)
	{
		close(data->pipe_fd[1]);
		data->prev_fd = data->pipe_fd[0];
	}
	data->i++;
	if (data->i < t_exec->cmd_count)
		ft_check_pipe(tokens);
}

void	ft_fork(t_data *data, t_list **env, t_list **export, t_token **tokens)
{
	t_token	*aux;

	aux = *tokens;
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (data->pid == 0)
	{
		signals();
		ft_dupv1(data);
		data->aux_head = ft_aux_lst(tokens, data->aux_head);
		ft_cmd_exec(&(data->aux_head), env, export, data->exec);
	}
	else
		ft_parent(data, tokens, data->exec);
}

int	ft_pipes(t_token **tokens, t_list **env, t_list **export, \
	t_executor *t_exec)
{
	t_data	*data;
	t_token	*temp;

	temp = *tokens;
	data = malloc(sizeof(t_data));
	data->i = 0;
	data->prev_fd = -1;
	data->aux_head = (*tokens);
	data->exec = t_exec;
	loop_pipes(data, tokens, env, export);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	ft_wait_childs_process(t_exec->cmd_count, t_exec);
	free(data);
	*tokens = temp;
	return (0);
}
