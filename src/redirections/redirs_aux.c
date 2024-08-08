/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:39:11 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 09:56:51 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_new_list_exec(t_token **tokens, t_token **aux)
{
	t_token	*temp;

	temp = *tokens;
	(*aux) = new_token((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	while ((*tokens))
	{
		while ((*tokens) && (*tokens)->tok != -1)
			(*tokens) = (*tokens)->next;
		if (*tokens)
		{
			add_token(aux, new_token((*tokens)->wrd, (*tokens)->hd_nbr));
			(*tokens) = (*tokens)->next;
		}
	}
	*tokens = temp;
}

int	ft_red_in(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	t_token	**aux;
	t_token	*temp;

	temp = *tokens;
	aux = malloc(sizeof(t_token));
	*aux = NULL;
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	dup2(t_exec->d_pipe->original_stdin, STDIN_FILENO);
	ft_free_tokens(*aux);
	free(aux);
	aux = NULL;
	*tokens = temp;
	return (0);
}

int	ft_red_out(t_token **tokens, t_list **env, t_list **export,
	t_executor *t_exec)
{
	t_token	**aux;
	t_token	*temp;

	temp = *tokens;
	aux = malloc(sizeof(t_token));
	*aux = NULL;
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
	ft_free_tokens(*aux);
	free(aux);
	aux = NULL;
	*tokens = temp;
	return (0);
}
