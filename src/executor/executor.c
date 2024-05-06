/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/06 13:48:23 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_child_process(t_executor *t_exec, t_token **tokens)
{
    char **argv;
    argv[0] = "ls";
    argv[1] = NULL;
    //SI ES UNA PIPE 
        //dup2(pipefd[1], 1);
        //close(pipefd[1]);
        //close(pipefd[0]);
    execve("/bin/ls", argv, NULL);
    exit(1);
}

void    executor(t_token **tokens, t_token **env, t_token **export)
{
    int status;
    t_executor  *t_exec;
    //int pipfd[2]
    if (!tokens || !*tokens)
        return (1/*decidir que s'ha de retornar*/);
    ft_count_pipes(); /*s'ha de fer*/
    if (ft_is_builtin(tokens) && t_exec->total_pipes == 0)
        return(builtins(tokens, export, env));
    t_exec->pid = fork();
    if (t_exec->pid < 0)
        return (0);
    if (t_exec->pid == 0)
        ft_child_process(t_exec, tokens);
    wait(&status);
    //SI ES UNA PIPE 
        //dup2(pipefd[0], 0);
        //close(pipefd[1]);
        //close(pipefd[0]);
    free(t_exec);   
}