/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/04 16:16:26 by pbotargu         ###   ########.fr       */
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
	if ((*tokens)->tok == 4)
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
		fd = open(filename_2(tokens), O_RDONLY);
	if (t_exec->redir_type == HEREDOC)
	{	
		ft_redir_here(tokens);	
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (1);
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
		fd = open(filename(tokens), O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(filename(tokens), O_CREAT | O_WRONLY | O_TRUNC, 0660);
	if (fd == -1)
		perror("Minishell");
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
	free(aux);
	return (0);
}

int	ft_red(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	ft_redirect(tokens, env, export, t_exec);
	if (t_exec->redir_type == REDIR_OUT || t_exec->redir_type == REDIR_OUT_APPEND)
		ft_red_out(tokens, env, export, t_exec);
	else if (t_exec->redir_type == REDIR_IN || t_exec->redir_type == HEREDOC)
		ft_red_in(tokens, env, export, t_exec);
	return (0);
}

int ft_redirs(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	ft_red(tokens, env, export, t_exec);
	return (1);
}
