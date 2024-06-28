/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:16:25 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/28 12:00:37 by pbotargu         ###   ########.fr       */
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
	if ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 1)
	{
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
	}
	printf("%s\n", (*tokens)->wrd);
}
int	ft_pipes(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int	new_pipe[2];
	int	prev_pipe[2] = {-1, -1};
	t_token *aux_head;
	
	while (t_exec->cmd_count != 0)
	{
		if (t_exec->total_pipes != 0)
			pipe(new_pipe);
		
		aux_head = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
		while ((*tokens) && ft_strcmp((*tokens)->wrd, "|") == 0)
		{
			add_token(&aux_head, new_token((*tokens)->wrd));
			(*tokens) = (*tokens)->next;
		}
		ft_check_pipe(tokens);
		if (t_exec->cmd_count > 1)
		{
			dup2(new_pipe[1], STDOUT_FILENO);
			close(new_pipe[0]);
			close(new_pipe[1]);
		}
		if (t_exec->cmd_count == 1)
		{
			dup2(new_pipe[0], STDIN_FILENO);
			close(new_pipe[0]);
			close(new_pipe[1]);
		}
		ft_executor_2(&aux_head, env, export, t_exec);
		t_exec->total_pipes--;
		t_exec->cmd_count--;
		prev_pipe[0] = new_pipe[0];
		prev_pipe[1] = new_pipe[1];

	}
	//ft_last_command(new_pipe, prev_pipe, tokens, t_exec);
	return (1);
}
