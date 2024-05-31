/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/31 09:46:14 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**env_list(char **envp)
{
	t_list	**env;
	t_list	*node;
	int		i;

	i = 0;
	env = (t_list **)malloc(sizeof(t_list *));
	if (!env)
		return (NULL);
	while (envp[i])
	{
		node = new_node(envp[i]);
		if (node)
			add_node(env, node);
		else
		{
			free(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}

int	ft_env(t_list	**env)
{
	int		i;
	t_list	*temp;

	temp = *env;
	i = 0;
	while (temp->next)
	{
		printf("%s=%s\n", temp->title, temp->def);
		temp = temp->next;
	}
	return (0);
}
