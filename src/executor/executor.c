/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/15 14:12:17 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_count_pipes(t_executor *t_exec, t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	t_exec->total_pipes = 0;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, "|"))
			t_exec->total_pipes++;
		temp = temp->next;
	}
}


/*void ft_child_process(t_executor *t_exec, t_token **tokens)
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
}*/


int	ft_commands(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (ft_is_redirection(tokens))
	{
		t_exec->exit_status = redirections(tokens, env, export, t_exec);
		return (1);
	}
	else if (ft_is_builtin(tokens) == 1)
	{
		t_exec->exit_status = builtins(tokens, export, env);
		return (1); 
	}
	else if (ft_exec(tokens, env, t_exec))
	{
		if (t_exec->execve_exec == 1)
			return (0);
		return (1);
	}
	return (0);
}
int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	//int status;
	//int pipfd[2]
	t_exec = malloc(sizeof(t_executor));
	if (!tokens || !*tokens)
	{
		free(t_exec);
		return (0);
	}
	ft_memset(t_exec, 0, sizeof(t_executor));
	ft_count_pipes(t_exec, tokens);
	if (t_exec->total_pipes == 0)
	{
		if (ft_commands(tokens, env, export, t_exec) == 0)
		{
			printf("%s", (*tokens)->wrd);
			printf(": command not found\n");
		}
	}

	/****************************************************/

	
	//if (ft_is_builtin(tokens) == 1 && t_exec->total_pipes == 0)
	//{
	//	t_exec->exit_status = builtins(tokens, export, env);
	//	return (1);/*revisar*/
	//}
	//else if (t_exec->total_pipes == 0) /*revisar condicions */
	//{
	//	t_exec->pid = fork();
	//	if (t_exec->pid < 0)
	//	{
	//		printf("pid < 0");
	//		return (0);/*revisar*/
	//	}
	//	if (t_exec->pid == 0)
	//		ft_exec(tokens, env, t_exec);/*s'ha de modificar*/
	//	else
	//		waitpid(t_exec->pid, 0, 0);/*aixo sha de revisar*/
	//}


	/***********************************************/

	
	/* t_exec->pid = fork();
	if (t_exec->pid < 0)
		return (1);
	if (t_exec->pid == 0)
		ft_child_process(t_exec, tokens);
	wait(&status);
	//SI ES UNA PIPE 
		//dup2(pipefd[0], 0);
		//close(pipefd[1]);
		//close(pipefd[0]);
	free(t_exec);*/
	return (0);
}
