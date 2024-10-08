/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/02 11:36:37 by pborrull         ###   ########.fr       */
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
	*env = NULL;
	while (envp[i])
	{
		node = new_node(envp[i]);
		if (node)
			add_node(env, node);
		else
		{
			ft_free_env(*env);
			return (NULL);
		}
		i++;
	}
	return (env);
}

int	ft_env(t_list	**env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		printf("%s=%s\n", temp->title, temp->def);
		temp = temp->next;
	}
	return (0);
}
