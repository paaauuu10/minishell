/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:11:00 by pborrull          #+#    #+#             */
/*   Updated: 2024/07/31 14:40:27 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cond(t_token **tokens)
{
	write(1, "exit\n", 5);
	if ((*tokens)->next && (*tokens)->next->wrd)
	{
		write(2, "Minishell> exit: ", 17);
		write(2, (*tokens)->next->wrd, ft_strlen((*tokens)->next->wrd));
		write(2, ": numeric argument required\n", 28);
		ft_exit_status(2, 1);
		exit(2);
	}
}

void	ft_exit(t_token **tokens, t_list **export, t_list **env, t_executor *t_exec)
{
	int	n;

	n = ft_atoi(ft_exit_status(0, 0));
	if ((*tokens)->next && ft_strcmp((*tokens)->next->wrd, "--"))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if ((*tokens)->next && (*tokens)->next->wrd)
		n = ft_atoi((const char *)(*tokens)->next->wrd);
	if ((*tokens)->next && (*tokens)->next->next && n != 255)
	{
		write(2, "Minishell> exit: too many arguments\n", 36);
		ft_exit_status(1, 1);
		return ;
	}
	else if ((*tokens)->next && n == 255)
		cond(tokens);
	else if ((*tokens) && !(*tokens)->next)
		write(1, "exit\n", 5);
	/*ft_free_env(*env);
	ft_free_env(*export);
	free(env);
	free(export);
	ft_free_mini(t_exec);*/
	(void)env;
	(void)export;
	(void)t_exec;
	exit(n);
}
