/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/10 12:57:47 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *filename_2(t_token **tokens)
{
	t_token *aux;

	aux = *tokens;
	while (aux->tok != 3)
		aux = aux->next;
	aux = aux->next;
	if (aux->tok == 3)
		aux = aux->next;
	return (aux->wrd);
}

char *filename(t_token **tokens)
{
	t_token *aux;

	aux = *tokens;
	while (aux->tok != 4)
		aux = aux->next;
	aux = aux->next;
	if (aux->tok == 4)
		aux = aux->next;
	return (aux->wrd);	
}

void	ft_new_list_exec_in(t_token **tokens, t_token **aux)
{
	(*aux) = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->tok == 3)
		return ;
	while ((*tokens) && ft_strcmp((*tokens)->wrd, "<") == 0)
	{
		add_token(aux, new_token((*tokens)->wrd));
		(*tokens) = (*tokens)->next;
	}
}

void	ft_new_list_exec(t_token **tokens, t_token **aux)
{
	(*aux) = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->tok == 4)
		return ;
	while ((*tokens) && ft_strcmp((*tokens)->wrd, ">") == 0)
	{
		add_token(aux, new_token((*tokens)->wrd));
		(*tokens) = (*tokens)->next;
	}
}

int	ft_red_in(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int fd;
	t_token **aux;

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
	if (t_exec->redir_type == HEREDOC)
		ft_redir_here(tokens);	
	if (fd != 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
	}
	ft_new_list_exec_in(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdin, STDIN_FILENO);
	free(aux);
	return (0);
}

int	ft_red_out(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int	fd;

	t_token **aux;

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

void	ft_count_redirects(t_token **tokens, t_executor *t_exec)
{
	t_token *temp;

	temp = (*tokens);
	t_exec->redir_out = 0;
	t_exec->redir_in = 0;
	while (temp->next)
	{
		if (temp->tok == 4 || temp->tok == 3)
		{
			if (temp->tok == 3)
				t_exec->redir_in++;
			else
				t_exec->redir_out++;
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
}

int	ft_aux_open(char *a, t_token **tokens, t_executor *t_exec)
{
	int fd;

	fd  = 0;
	if (t_exec->redir_type == REDIR_OUT_APPEND)
		fd = open(a, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(a, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	else if (t_exec->redir_type == REDIR_IN)
		fd = open(a, O_RDONLY);
	else if (t_exec->redir_type == HEREDOC)
		ft_redir_here(tokens);
	if (fd == -1)
	{
		ft_exit_status(1, 1);
		perror("Minishell");
		return (0);
	}
	close(fd);
	return (1);
}

void	ft_last_redir(t_token **tokens, t_executor *t_exec)
{
	while ((*tokens) && ((*tokens)->tok != 3 && (*tokens)->tok != 4))
		(*tokens) = (*tokens)->next;
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
				ft_redir_here(tokens);
			(*tokens) = (*tokens)->next; 
		}
	}
	t_exec->filename = (*tokens)->wrd;
}

int	ft_open(t_token **tokens, t_executor *t_exec)
{
	int	i;
	t_token *temp;
	int total;

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
			temp = temp->next;
			if (temp->tok == 3)
				t_exec->redir_type = HEREDOC;
			else
				t_exec->redir_type = REDIR_OUT_APPEND;
		}
		if (!(ft_aux_open(temp->wrd, tokens, t_exec)))
			return (0);
		i++;
	}
	ft_last_redir(&temp, t_exec);
	return (1);
}

int ft_redirs(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int i;

	i = 0;
	ft_count_redirects(tokens, t_exec);
	if (!(ft_open(tokens, t_exec)))
		return (1);
	if (t_exec->redir_type == REDIR_OUT || t_exec->redir_type == REDIR_OUT_APPEND)
		ft_red_out(tokens, env, export, t_exec);
	else if (t_exec->redir_type == REDIR_IN || t_exec->redir_type == HEREDOC)
		ft_red_in(tokens, env, export, t_exec);
	return (0);
}
