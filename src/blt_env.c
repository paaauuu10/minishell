/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/07 15:06:48 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**env_list(char **envp)
{
	t_list	**env;
	int		i;

	i = 0;
	env = (t_list **)malloc(sizeof(t_list *));
	if (!env)
		return (NULL);
	while (envp[i])
		add_node(env, new_node(envp[i++]));
/*	while ((*env))
	{
		printf("Title is: %s ", (*env)->title);
		printf("Def is:%s\n", (*env)->def);
		(*env) = (*env)->next;
	}*/
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
/*int	ft_env(char	**env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}*/
