/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:15:02 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/24 13:54:14 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_strcmp_hd(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	no_loop_heredoc(char *str)
{
	char	*line;

	while (42)
	{
		line = readline("> ");
		if (ft_strcmp_hd(line, str) == 0)
			break ;
		free(line);
	}
}

void	bucle_heredoc(int fd, char *str)
{
	char	*line;
	int		fd1;

	(void)fd;
	signals();
	fd1 = open(".temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (42)
	{
		line = readline("> ");
		if (ft_strcmp_hd(line, str) == 0)
			break ;
		write(fd1, line, ft_strlen(line));
		write(fd1, "\n", 1);
		free(line);
	}
	close(fd1);
	fd1 = open(".temp", O_RDONLY);
	dup2(fd1, STDIN_FILENO);
	close(fd1);
}

int	init_heredoc(char *str)
{
	int		fd[2];

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	else
		bucle_heredoc(fd[1], str);
	close(fd[1]);
	close(fd[0]);
	return (0);
}

int	ft_redir_here(t_token **tokens)
{
	t_token	*node;

	node = *tokens;
	while (node != NULL)
	{
		if (node->tok == 3)
		{
			while (ft_strcmp(node->wrd, "<") == 0)
				node = node->next;
			node = node->next;
			node = node->next;
			if ((init_heredoc(node->wrd)))
				return (1);
		}
		node = node->next;
	}
	return (0);
}

/*int	open_heredoc(t_token **tokens, t_executor *t_exec)
{
	int	fd;
}*/
