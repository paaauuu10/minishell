/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:46 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/25 13:35:38 by pbotargu         ###   ########.fr       */
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
	while (temp->next)
	{
		if (temp->tok == 4 || temp->tok == 3)
		{
			if (temp->tok == 3)
			{
				t_exec->redir_in++;
				t_exec->flag_red = LAST_GLB_IN;
			}
			else
			{
				t_exec->flag_red = LAST_GLB_OUT;
				t_exec->redir_out++;
			}
			if (temp->next)
			{
				temp = temp->next;
				if ((temp->tok == 4 || temp->tok == 3) && temp->next)
					temp = temp->next;
			}
		}
		if (temp->next)
			temp = temp->next;
	}
	if (t_exec->redir_out > 0 && t_exec->redir_in > 0)
	{
		ft_find_last_in(tokens, t_exec);
		ft_find_last_out(tokens, t_exec);
	}
}

int	ft_heredoc_create(t_token **tokens, int hd_nbr, t_executor *t_exec)
{
	char	*tmp_dir;
	int		fd_tmp;
	char	*line;

	while ((*tokens)->tok == 3)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		else
			return (1);
	}
	(*tokens)->hd_nbr = hd_nbr;
	tmp_dir = ft_strjoin("/tmp/heredoc", ft_itoa(hd_nbr));
	fd_tmp = open(tmp_dir, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	line = readline("> ");
	while (line && ft_strcmp(line, (*tokens)->wrd) == 0)
	{
		write(fd_tmp, line, ft_strlen(line));
		write(fd_tmp, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd_tmp);
	//free(line);
	//free(redir->fname);
	//redir->fname = ft_strdup(tmp_dir);
	//free(tmp_dir);
	(void)t_exec;
	//set_signals(PARENT);
	return (0);
}

int	heredoc_v2(t_token **tokens, t_executor *t_exec)
{
	int			hd_nbr;
	t_token		*temp;

	hd_nbr = 1;
	temp = *tokens;
	while (temp)
	{
		if (temp->tok == 3 && temp->next && temp->next->tok == 3)
		{
			ft_heredoc_create(&temp, hd_nbr, t_exec);
			hd_nbr++;
		}
		temp = temp->next;
	}
	return (0);
}
