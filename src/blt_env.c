/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/03 09:39:45 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
