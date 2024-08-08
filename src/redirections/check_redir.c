/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:46 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 10:36:44 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirection(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, ">") || \
		ft_strcmp(temp->wrd, "<") || \
		ft_strcmp(temp->wrd, ">>") || \
		ft_strcmp(temp->wrd, "<<"))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	ft_count_redirects(t_token **tokens, t_executor *t_exec)
{
	t_token	*temp;

	temp = (*tokens);
	t_exec->redir_out = 0;
	t_exec->redir_in = 0;
	t_exec->n_redir = -1;
	help_count(&temp, t_exec);
}

void	help_heredoc(int fd_tmp, char *tmp_dir, char *a)
{
	char	*line;

	fd_tmp = open(tmp_dir, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	line = readline("> ");
	while (line && ft_strcmp(line, a) == 0)
	{
		write(fd_tmp, line, ft_strlen(line));
		write(fd_tmp, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd_tmp);
	free(line);
}

int	ft_heredoc_create(t_token **tokens, int hd_nbr)
{
	char	*tmp_dir;
	int		fd_tmp;
	char	*it;

	fd_tmp = 0;
	it = ft_itoa(hd_nbr);
	while ((*tokens)->tok == 3)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		else
			return (1);
	}
	(*tokens)->hd_nbr = hd_nbr;
	tmp_dir = ft_strjoin("/tmp/heredoc", it);
	free(it);
	help_heredoc(fd_tmp, tmp_dir, (*tokens)->wrd);
	free(tmp_dir);
	return (0);
}

int	heredoc_v2(t_token **tokens)
{
	int			hd_nbr;
	t_token		*temp;

	hd_nbr = 1;
	temp = *tokens;
	while (temp)
	{
		if (temp->tok == 3 && temp->next && temp->next->tok == 3)
		{
			ft_heredoc_create(&temp, hd_nbr);
			hd_nbr++;
		}
		temp = temp->next;
	}
	return (0);
}
