/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:38:07 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 10:02:46 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_exec(t_token **tokens, t_list **e, t_executor *t_exec)
{
	t_exec->new_envp = ft_copy_env(e);
	ft_exit_status(0, 1);
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	heredoc_v2(tokens);
}

void	run_exec(t_token **tokens, t_list **env, \
		t_list **export, t_executor *t_exec)
{
	if (t_exec->total_pipes == 0 && !is_redirection(tokens) \
		&& ft_is_builtin(tokens))
		builtins(tokens, env, export);
	else if (t_exec->total_pipes == 0 && !is_redirection(tokens))
		ft_only_cmd(tokens, env, export, t_exec);
	else if (t_exec->total_pipes == 0 && ft_redirect(tokens, t_exec))
		ft_redirs(tokens, env, export, t_exec);
	else
		ft_pipes(tokens, env, export, t_exec);
}

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
