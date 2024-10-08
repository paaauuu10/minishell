/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:50:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/08 11:32:05 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expansor_while(char *temp, int i, t_list **env)
{
	int		j;
	char	*r;

	while (temp[i])
	{
		while (temp[i] && temp[i] != '$')
			i++;
		if (temp[i] && temp[i] == '$' && temp[++i] && temp[i] != ' ')
		{
			r = ft_str_list(env, &temp[--i]);
			if (r)
			{
				if ((*r) != '_')
				{
					j = i + ft_strlen(r);
					temp = ft_strcat(temp, r, j);
				}
				i++;
				free(r);
			}
			else
				return (temp);
		}
	}
	return (temp);
}

char	*ft_expansor(t_list **env, char *s)
{
	int		i;

	i = 0;
	if (ft_strcmp(s, "$?"))
	{
		free(s);
		s = ft_itoa(ft_exit_status(0, 0));
	}
	s = ft_expansor_while(s, i, env);
	return (s);
}
