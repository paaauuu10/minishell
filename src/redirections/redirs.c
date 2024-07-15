/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/15 14:21:40 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_new_list_exec(t_token **tokens, t_token **aux)
{
	(*aux) = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->tok == 4 || (*tokens)->tok == 3)
		return ;
	while ((*tokens) && (*tokens)->tok != 4 && (*tokens)->tok != 3)
	{
		add_token(aux, new_token((*tokens)->wrd));
		(*tokens) = (*tokens)->next;
	}
}

int	ft_red_in(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	int		fd;
	t_token	**aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	fd = 0;
	if (t_exec->redir_type == REDIR_IN)
	{
		fd = open(t_exec->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_reset_fd(t_exec);
			perror("Minishell ");
			ft_exit_status(1, 1);
		}
	}
	if (fd != 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
	}
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdin, STDIN_FILENO);
	free(aux); //free bucle
	return (0);
}

int	ft_red_out(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	int		fd;
	t_token	**aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	fd = 0;
	if (t_exec->redir_type == REDIR_OUT_APPEND)
		fd = open(t_exec->filename, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(t_exec->filename, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	if (fd == -1)
	{
		ft_reset_fd(t_exec);
		perror("Minishell");
		ft_exit_status(1, 1);
		return (1); //que s'ha de retornar?
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
	free(aux);
	return (0);
}

void	ft_find_last_in(t_token **tokens, t_executor *t_exec)
{
	t_token	*temp;
	int		i;

	temp = *tokens;
	i = 0;
	while (i < t_exec->redir_in)
	{
		while (temp->tok != 3 && temp->next)
			temp = temp->next;
		if (temp->tok == 3)
		{
			i++;
			t_exec->red_typ_3 = REDIR_IN;
			temp = temp->next;
			if (temp->tok == 3)
			{
				temp = temp->next;
				t_exec->red_typ_3 = HEREDOC;
			}
		}
	}
	temp->flag = LAST_IN;
}

void	ft_find_last_out(t_token **tokens, t_executor *t_exec)
{
	t_token	*temp;
	int		i;

	temp = *tokens;
	i = 0;
	while (i < t_exec->redir_out)
	{
		while (temp->tok != 4 && temp->next)
			temp = temp->next;
		if (temp->tok == 4)
		{
			i++;
			t_exec->red_typ_4 = REDIR_OUT;
			temp = temp->next;
			if (temp->tok == 4 && temp->next)
			{
				temp = temp->next;
				t_exec->red_typ_4 = REDIR_OUT_APPEND;
			}
		}
	}
	temp->flag = LAST_OUT;
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

int	ft_aux_open(char *a, t_executor *t_exec)
{
	int	fd;

	fd = 0;
	if (t_exec->redir_type == REDIR_OUT_APPEND)
		fd = open(a, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(a, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	else if (t_exec->redir_type == REDIR_IN)
		fd = open(a, O_RDONLY);
	else if (t_exec->redir_type == HEREDOC)
	{
		no_loop_heredoc(a);
	}
	if (fd == -1)
	{
		ft_exit_status(1, 1);
		perror("Minishell");
		return (0);
	}
	if (fd > 0)
		close(fd);
	return (1);
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
	i = 0;
	while (i < total - 1)
	{
		while (temp->tok != 4 && temp->tok != 3)
			temp = temp->next;
		if (temp->tok == 4)
			t_exec->redir_type = REDIR_OUT;
		else
			t_exec->redir_type = REDIR_IN;
		temp = temp->next;
		if ((temp->tok == 4 || temp->tok == 3) && temp->next)
		{
			if (temp->tok == 3)
				t_exec->redir_type = HEREDOC;
			else
				t_exec->redir_type = REDIR_OUT_APPEND;
			temp = temp->next;
		}
		if (temp->flag == 0)
		{
			if (!(ft_aux_open(temp->wrd, t_exec)))
				return (0);
		}
		i++;
	}
	ft_last_redir(&temp, t_exec);
	return (1);
}

int	ft_last_two(t_token **tokens, t_list **env, t_list **ex, t_executor *t_exec)
{
	int		fd;
	int		fd1;
	t_token	*temp;
	t_token	**aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	fd = 0;
	fd1 = 0;
	temp = *tokens;
	while (temp->flag != LAST_IN)
		temp = temp->next;
	if (t_exec->red_typ_3 == REDIR_IN)
	{
		fd = open(temp->wrd, O_RDONLY);
		if (fd == -1)
		{
			ft_reset_fd(t_exec);
			perror("Minishell ");
			ft_exit_status(1, 1);
		}
	}
	else if (t_exec->red_typ_3 == HEREDOC)
		init_heredoc(temp->wrd);
	if (fd != 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
	}
	temp = *tokens;
	while (temp->flag != LAST_OUT)
		temp = temp->next;
	if (t_exec->red_typ_4 == REDIR_OUT_APPEND)
		fd1 = open(temp->wrd, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->red_typ_4 == REDIR_OUT)
		fd1 = open(temp->wrd, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	if (fd1 == -1)
	{
		ft_reset_fd(t_exec);
		perror("Minishell");
		ft_exit_status(1, 1);
		return (1); //que s'ha de retornar?
	}
	if (dup2(fd1, STDOUT_FILENO) == -1)
		return (1);
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, ex, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
	free(aux);
	return (0);
}

int	ft_redirs(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	int	i;

	i = 0;
	ft_count_redirects(tokens, t_exec);
	if (!(ft_open(tokens, t_exec)))
		return (1);
	if (t_exec->redir_in > 0 && t_exec->redir_out > 0)
	{
		if (ft_last_two(tokens, env, export, t_exec) > 0)
			return (1);
	}
	else if (t_exec->redir_type == REDIR_OUT || t_exec->redir_type == REDIR_OUT_APPEND)
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
