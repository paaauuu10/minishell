/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:38:07 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/07 15:50:00 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_aux_lst(t_token **tokens, t_token *aux_head)
{
	aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
		{
			add_token(&aux_head, new_token((*tokens)->wrd, (*tokens)->hd_nbr));
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			else
				break ;
		}
	}
	return (aux_head);
}

void	ft_dupv1(t_data *data)
{
	if (data->prev_fd != -1)
	{
		dup2(data->prev_fd, STDIN_FILENO);
		close(data->prev_fd);
	}
	if (data->i < data->exec->cmd_count - 1)
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
	}
}

void	loop_pipes(t_data *data, t_token **tokens, t_list **env, \
		t_list **export)
{
	while (data->i < data->exec->cmd_count)
	{
		if (data->i < data->exec->cmd_count - 1)
		{
			if (pipe(data->pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		ft_fork(data, env, export, tokens);
	}
}
