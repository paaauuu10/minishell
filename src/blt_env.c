/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/30 14:45:32 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(t_token	**env)
{
	int		i;
	t_token	*temp;

	temp = *env;
	i = 0;
	while (temp->next)
	{
		printf("%s\n", temp->wrd);
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
