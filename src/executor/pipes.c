/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:16:25 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/02 11:10:38 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_dup2(int new_pipe, int prev_pipe, t_executor *t_exec)
{
	if (t_exec->total_pipes != 0 && t_exec->cmd_count > 0)
	{
		close(prev_pipe[OUT]);
		close(prev_pipe[IN]);
	}
	//if (t_exec->total_pipes == 0) //revisar aixo
	if (t_exec->total_pipes != 0)
	{
		close()
	}

	
	
}*/
//void	ft_last_command(int new_pipe, int prev_pipe, t_token **tokens,t_executor *t_exec)
//{
//}
void ft_check_pipe(t_token **tokens)
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

int ft_pipes(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec) {
    int pipe_fd[2];
    int prev_fd = -1;
    int i = 0;
    pid_t pid;
    t_token *aux_head;
	t_token *first = (*tokens);
	(void)export;
	aux_head = (*tokens);
	//if (ft_redirs(tokens, env, export, t_exec))
	//	return (0);
	//(*tokens) = aux_head;
	while (i < t_exec->cmd_count) {
        if (i < t_exec->cmd_count - 1) {
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Proceso hijo
			if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < t_exec->cmd_count - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
			{
				if (!(*tokens)->next)
					break ;
				add_token(&aux_head, new_token((*tokens)->wrd));
				(*tokens) = (*tokens)->next;
			}
			if (ft_redirect(&aux_head, env, export, t_exec) != 0)
			{
				ft_redirs(&aux_head, env, export, t_exec);
				exit (0); //revisar 
			}
			else if (ft_is_builtin(tokens))
				exit(builtins(&aux_head, env, export));
			else
			{
				ft_exec(&aux_head, env, t_exec);
            	ft_print_error(first->wrd);
				ft_print_error(": command not found\n");// Solo si execvp falla
            }
			exit(EXIT_FAILURE);
        } else { // Proceso padre
            if (prev_fd != -1) {
                close(prev_fd);
            }
            if (i < t_exec->cmd_count - 1) {
                close(pipe_fd[1]);
                prev_fd = pipe_fd[0];
            }

            i++;
            if (i < t_exec->cmd_count)
				ft_check_pipe(tokens);
        }
    }

    if (prev_fd != -1) {
        close(prev_fd);
    }

    i = 0;
    while (i < t_exec->cmd_count) {
        wait(NULL);
        i++;
    }

    return 0;
}
