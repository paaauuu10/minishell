/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 09:53:50 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_aux_v2(int fd, t_executor *t_exec)
{
	if (fd == -1)
	{
		ft_exit_status(1, 1);
		perror("Minishell");
		return (1);
	}
	if (t_exec->redir_type == REDIR_OUT_APPEND || \
		t_exec->redir_type == REDIR_OUT)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
	}
	close(fd);
	return (0);
}

int	ft_aux_open(char *a, int hd, t_executor *t_exec)
{
	int		fd;
	char	*filename;
	char	*it;

	it = ft_itoa(hd);
	fd = 0;
	if (t_exec->redir_type == REDIR_OUT_APPEND)
		fd = open(a, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(a, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	else if (t_exec->redir_type == REDIR_IN)
		fd = open(a, O_RDONLY);
	else if (t_exec->redir_type == HEREDOC)
	{
		filename = ft_strjoin("/tmp/heredoc", it);
		fd = open(filename, O_RDONLY);
		free(filename);
	}
	free(it);
	if (ft_aux_v2(fd, t_exec))
		return (1);
	return (0);
}

void	ft_last_redir(t_token **tokens, t_executor *t_exec)
{
	t_token	*temp;

	temp = *tokens;
	while ((*tokens) && ((*tokens)->tok != 3 && (*tokens)->tok != 4))
		(*tokens) = (*tokens)->next;
	if (((*tokens)->tok == 4 || (*tokens)->tok == 3) && (*tokens)->next)
	{
		if ((*tokens)->tok == 4)
			t_exec->redir_type = REDIR_OUT;
		else
			t_exec->redir_type = REDIR_IN;
		(*tokens) = (*tokens)->next;
		if ((*tokens)->tok == 4 || (*tokens)->tok == 3)
		{
			if ((*tokens)->tok == 4)
				t_exec->redir_type = REDIR_OUT_APPEND;
			else
			{
				t_exec->redir_type = HEREDOC;
				ft_redir_here(&temp);
			}
			(*tokens) = (*tokens)->next;
		}
	}
	t_exec->filename = (*tokens)->wrd;
}

int	ft_open(t_token **tokens, t_executor *t_exec)
{
	int		i;
	t_token	*temp;
	int		total;

	total = t_exec->redir_in + t_exec->redir_out;
	temp = (*tokens);
	i = 1;
	while (i <= total)
	{
		while ((temp->tok != 4 && temp->tok != 3) && temp->next)
			temp = temp->next;
		determine_redirection_type(&temp, t_exec);
		if (temp->flag == 0)
		{
			if ((ft_aux_open(temp->wrd, temp->hd_nbr, t_exec)))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_redirs(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	int	i;

	i = 0;
	ft_count_redirects(tokens, t_exec);
	if ((ft_open(tokens, t_exec)))
		return (1);
	if (t_exec->redir_type == REDIR_OUT || \
		t_exec->redir_type == REDIR_OUT_APPEND)
	{
		if (ft_red_out(tokens, env, export, t_exec) > 0)
			return (1);
	}
	else if (t_exec->redir_type == REDIR_IN || t_exec->redir_type == HEREDOC)
	{
		if (ft_red_in(tokens, env, export, t_exec) > 0)
			return (1);
	}
	return (0);
}
