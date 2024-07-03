/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:16:25 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/03 17:00:54 by pbotargu         ###   ########.fr       */
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

t_token	*ft_aux_lst(t_token **tokens, t_token *aux_head)
{
	aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
		{
			add_token(&aux_head, new_token((*tokens)->wrd));
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			else
				break ;
		}
	}
	return (aux_head);
}

void	ft_cmd_exec(t_token **tokens, t_list **env, t_list **export, \
		t_executor *t_exec)
{
	if (ft_redirect(tokens, env, export, t_exec) != 0)
	{
		ft_redirs(tokens, env, export, t_exec);
		exit(0);
	}
	else if (ft_is_builtin(tokens))
		exit(builtins(tokens, env, export));
	else
	{
		ft_exec(tokens, env, t_exec);
		perror("execvp");
	}
	exit(EXIT_FAILURE);
}

int	ft_pipes(t_token **tokens, t_list **env, t_list **export, \
	t_executor *t_exec)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	/*int		pipe_fd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	t_token	*aux_head;

	i = 0;
	prev_fd = -1;
	aux_head = (*tokens);*/
	data->i = 0;
	data->prev_fd = -1;
	data->aux_head = (*tokens);
	while (data->i < t_exec->cmd_count)
	{
		if (data->i < t_exec->cmd_count - 1)
		{
			if (pipe(data->pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		data->pid = fork();
		if (data->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (data->pid == 0)
		{
			if (data->prev_fd != -1)
			{
				dup2(data->prev_fd, STDIN_FILENO);
				close(data->prev_fd);
			}
			if (data->i < t_exec->cmd_count - 1)
			{
				dup2(data->pipe_fd[1], STDOUT_FILENO);
				close(data->pipe_fd[0]);
				close(data->pipe_fd[1]);
			}
			data->aux_head = ft_aux_lst(tokens, data->aux_head);
			ft_cmd_exec(&(data->aux_head), env, export, t_exec);
		}
		else
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
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	ft_wait_childs_process(t_exec->cmd_count, t_exec);
	free(data);
	return (0);
}
