/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:16:25 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/03 16:05:15 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_pipe(t_token **tokens)
{
	while ((*tokens) && (*tokens)->tok != 2)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		else
			break ;
	}
	if ((*tokens) && (*tokens)->tok == 2)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
	}
}

t_token	*ft_pipes_aux(t_token **tokens, t_token *aux_head)
{
	aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
	{
		(*tokens) = (*tokens)->next;
		while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
		{
			add_token(&aux_head, new_token((*tokens)->wrd));
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			else
				break ;
		}
	}
	return (aux_head);
}

int	ft_pipes(t_token **tokens, t_list **env, t_list **export, \
	t_executor *t_exec)
{
	int		pipe_fd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	t_token	*aux_head;

	i = 0;
	prev_fd = -1;
	aux_head = (*tokens);
	while (i < t_exec->cmd_count)
	{
		if (i < t_exec->cmd_count - 1)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid  == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < t_exec->cmd_count - 1)
			{
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            aux_head = ft_pipes_aux(tokens, aux_head);
			//aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
			//if ((*tokens)->next)
			//{
			//	(*tokens) = (*tokens)->next;
			//	while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
			//	{
			//		add_token(&aux_head, new_token((*tokens)->wrd));
			//		if ((*tokens)->next)
			//			(*tokens) = (*tokens)->next;
			//		else
			//			break;
			//	}
			//}
			if (ft_redirect(&aux_head, env, export, t_exec) != 0)
			{
				ft_redirs(&aux_head, env, export, t_exec);
				exit(0);
			}
			else if (ft_is_builtin(&aux_head))
				exit(builtins(&aux_head, env, export));
			else
			{
				ft_exec(&aux_head, env, t_exec);
            	perror("execvp"); // Solo si execvp falla
            }
			exit(EXIT_FAILURE);
        } 
		else 
		{
			if (prev_fd != -1) 
                close(prev_fd);
            if (i < t_exec->cmd_count - 1)
			{
                close(pipe_fd[1]);
                prev_fd = pipe_fd[0];
            }
            i++;
            if (i < t_exec->cmd_count)
				ft_check_pipe(tokens);
        }
    }

    if (prev_fd != -1)
		close(prev_fd);
    i = 0;
	ft_wait_childs_process(t_exec->cmd_count, t_exec);
    return 0;
}
