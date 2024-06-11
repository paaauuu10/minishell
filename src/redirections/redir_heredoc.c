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

void	bucle_heredoc(int fd, char *str)
{
	char	*line;

	signals();
	while (42)
	{
		line = readline("> ");
		if (ft_strcmp_hd(line, str) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 2);
		free(line);
	}
}

static int	init_heredoc(char *str)
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
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

int	ft_redir_here(t_token **tokens)
{
	t_token	*node;

	node = *tokens;
	while (node != NULL)
	{
		if (node->tok == 3 /*|| node->exp_type == HEREDOC_PIPE*/)
			{
			while (ft_strcmp(node->wrd, "<") == 0)
				node = node->next;
			node = node->next;
			node = node->next;
			if (init_heredoc(node->wrd))
				return (1);
		}
		node = node->next;
	}
	return (0);
}
