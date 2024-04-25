/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/23 14:40:20 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
