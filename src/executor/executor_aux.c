/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:45:39 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/15 13:43:23 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********************************************************************

							URGENT FER AIXO

*********************************************************************/

int	ft_aux_abs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i] != '/')
		i--;
	return (i + 1);
}

void	ft_aux_exec_absolut(char **cmd_argv, t_token **tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		if ((*tokens)->wrd[0] == '/')
		{
			cmd_argv[i] = ft_substr((*tokens)->wrd, \
			ft_aux_abs((*tokens)->wrd), ft_strlen((*tokens)->wrd));
			if (!cmd_argv[i])
				exit(1);
			//ft_error_system(MALLOC_ERROR);
			*tokens = (*tokens)->next;
			if (!*tokens || (*tokens)->tok == 2 || (*tokens)->tok == 3 || \
				(*tokens)->tok == 4)
				break ;
			i++;
		}
		cmd_argv[i] = ft_strdup((*tokens)->wrd);
		if (!cmd_argv[i])
			exit (1);
		//ft_error_system(MALLOC_ERROR);
		*tokens = (*tokens)->next;
		i++;
	}
}

void	ft_exec_absolut(t_token **tokens, t_executor *t_exec)
{
	t_exec->absolute_path = (*tokens)->wrd;
	t_exec->cmd_argv = (char **)malloc(sizeof(char *) * \
	(ft_list_size(*tokens) + 1));
	if (!t_exec->cmd_argv)
		exit(1);
	//ft_error_system(MALLOC_ERROR);
	if (access(t_exec->absolute_path, F_OK) != 0)
	{
		//ft_error_cmd(d_exec->absolute_path, 2);
		perror("Minishell: ");
		exit(127);
	}
	t_exec->cmd_argv[ft_list_size(*tokens)] = NULL;
	ft_aux_exec_absolut(t_exec->cmd_argv, tokens);
	if (access(t_exec->absolute_path, X_OK) == 0)
		execve(t_exec->absolute_path, t_exec->cmd_argv, t_exec->new_envp);
	else
	{
		//ft_error_cmd(d_exec->cmd_argv[0], 3);
		perror ("Minishell: ");
		exit(126);
	}
	//ft_error_cmd(t_exec->cmd_argv[0], 1);
	exit(127);
}
