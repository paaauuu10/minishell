/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/06 12:43:48 by pbotargu         ###   ########.fr       */
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
		if (temp->tok == 2)
			t_exec->total_pipes++;
		temp = temp->next;
	}
	t_exec->d_pipe->pipecounter = t_exec->total_pipes;
	t_exec->cmd_count = t_exec->total_pipes + 1;
}

int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	t_token	*aux;

	aux = *tokens;
	(void)export;
	t_exec->pid = fork();
	if (t_exec->pid == 0)
	{
		signals();
		if ((*tokens)->wrd[0] == '/' || (*tokens)->wrd[0] == '.')
			ft_exec_absolut(tokens, t_exec);
		else
			ft_exec(tokens, env, t_exec);
		ft_print_error(aux->wrd);
		*tokens = aux;
		write(2, ": command not found\n", 20);
		exit(127);
	}
	else
		ft_wait_one_child_process();
	return (0); //revisar
}

/**********************************************************************
				TRYING NEW EXECUTOR
**********************************************************************/
int	ft_executor_2(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	if (ft_is_builtin(tokens))
		builtins(tokens, env, export);
	else
		ft_only_cmd(tokens, env, export, t_exec);
	return (0);
}

void	ft_free_mini(t_executor *t_exec)
{
	int	i;

	i = 0;
	free(t_exec->d_pipe);
	while (t_exec->new_envp[i])
		free(t_exec->new_envp[i++]);
	free(t_exec->new_envp);
	free(t_exec);
}

int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;

	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); //revisar
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); //revisar
	if (!tokens || !*tokens)
	{
		free(t_exec);
		return (0);
	}
	t_exec->new_envp = ft_copy_env(env);
	ft_exit_status(0, 1);
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	heredoc_v2(tokens, t_exec);
	/*while (*tokens)
	{
		printf("Paraula: %s  HD_NBR:  %d\n", (*tokens)->wrd, (*tokens)->hd_nbr);
		(*tokens) = (*tokens)->next;
	}*/
	if ((*tokens)->wrd[0] == '$' && (*tokens)->wrd[1])
	{	
		ft_free_mini(t_exec);
		return (1);
	}
	if (t_exec->total_pipes == 0 && !is_redirection(tokens) && ft_is_builtin(tokens))
		builtins(tokens, env, export);
	else if (t_exec->total_pipes == 0 && !is_redirection(tokens))
		ft_only_cmd(tokens, env, export, t_exec);
	else if (t_exec->total_pipes == 0 && ft_redirect(tokens, t_exec))
		ft_redirs(tokens, env, export, t_exec);
	else
		ft_pipes(tokens, env, export, t_exec);
	ft_reset_fd(t_exec);
	ft_free_mini(t_exec);
	return (0);
}
