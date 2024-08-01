/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:50:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/01 10:44:31 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expansor_while(char *temp, int i, t_list **env)
{
	int		j;
	char	*r;

	j = 0;
	while (temp[i])
	{
		while (temp[i] && temp[i] != '$')
			i++;
		if (temp[i] && temp[i++] == '$')
		{
			r = ft_str_list(env, &temp[--i]);
			if (r)
			{
				if ((*r) != '_') //&& !ft_isalnum(*r))
				{
					j = i + ft_strlen(r);
					temp = ft_strcat(temp, r, j);
				}
				i++;
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
		s = ft_itoa(ft_exit_status(0, 0));
	s = ft_expansor_while(s, i, env);
	return (s);
}
