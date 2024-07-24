/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:39:11 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/24 15:58:33 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_new_list_exec(t_token **tokens, t_token **aux)
{
	(*aux) = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->tok == 4 || (*tokens)->tok == 3)
		return ;
	while ((*tokens) && (*tokens)->tok != 4 && (*tokens)->tok != 3)
	{
		add_token(aux, new_token((*tokens)->wrd, (*tokens)->hd_nbr));
		(*tokens) = (*tokens)->next;
	}
}

int	ft_red_in(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	//int		fd;
	t_token	**aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	//fd = 0;
	/*if (t_exec->redir_type == REDIR_IN)
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
	}*/
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	//close(fd);
	dup2(t_exec->d_pipe->original_stdin, STDIN_FILENO);
	free(aux); //free bucle
	return (0);
}

int	ft_red_out(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	//int		fd;
	t_token	**aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	//fd = 0;
	/*if (t_exec->redir_type == REDIR_OUT_APPEND)
		fd = open(t_exec->filename, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(t_exec->filename, O_CREAT | O_WRONLY | O_TRUNC, 0660);
	if (fd == -1)
	{
		ft_reset_fd(t_exec);
		perror("Minishell");
		ft_exit_status(1, 1);
		return (1); // que s'ha de retornar? 
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);*/
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	//close(fd);
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
