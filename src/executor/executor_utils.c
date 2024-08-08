/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:09 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 13:47:27 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_list_size(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->wrd != NULL)
	{
		token = token->next;
		i++;
	}
	return (i);
}

int	ft_path(t_token **tokens, t_list **env, t_executor **t_exec)
{
	t_list	*temp;

	temp = *env;
	while ((*env) && ft_strncmp("PATH", (*env)->title, 4) != 0)
	{
		*env = (*env)->next;
		if (!(*env))
			return (127);
	}
	(*t_exec)->path = ft_split((*env)->def, ':');
	*env = temp;
	if (!(*t_exec)->path)
		return (1);
	(*t_exec)->cmd = ft_strjoin("/", (*tokens)->wrd);
	if (!(*t_exec)->cmd)
		return (1);
	return (0);
}

int	ft_exec_cmd(t_executor **t_exec)
{
	int	i;

	i = 0;
	while ((*t_exec)->path[i])
	{
		(*t_exec)->absolute_path = ft_strjoin((*t_exec)->path[i], \
		(*t_exec)->cmd);
		if (!(*t_exec)->cmd)
			exit (1);
		if (access((*t_exec)->absolute_path, X_OK) == 0)
			return (1);
		free((*t_exec)->absolute_path);
		i++;
	}
	return (0);
}

int	ft_exec(t_token **tokens, t_list **env, t_executor *t_exec)
{
	int		i;
	t_token	*temp;

	temp = *tokens;
	i = 0;
	if (ft_path(tokens, env, &t_exec) != 0)
		return (1);
	t_exec->cmd_argv = (char **)malloc(sizeof(char *) * \
	(ft_list_size(*tokens) + 1));
	if (!t_exec->cmd_argv)
		return (1);
	t_exec->cmd_argv[ft_list_size(*tokens)] = NULL;
	while (*tokens)
	{
		t_exec->cmd_argv[i] = ft_strdup((*tokens)->wrd);
		if (!t_exec->cmd_argv[i])
			return (1);
		*tokens = (*tokens)->next;
		i++;
	}
	i = 0;
	if (ft_exec_cmd(&t_exec))
		execve(t_exec->absolute_path, t_exec->cmd_argv, t_exec->new_envp);
	*tokens = temp;
	return (0);
}
