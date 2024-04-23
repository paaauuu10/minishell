/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:50:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/23 14:45:57 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expansor(char **envp, char *s)
{
	int		i;
	char	*r;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] && s[i++] == '$')
	{
		if (envp[0])
		{
			r = ft_str_matrix(envp, s);
			if (r)
			{
				if ((*r) != '_' && !ft_isalnum(*r++))
				{
					ft_printf("%s\n", r);
					return (r);
				}
			}
		}
	}
	return (NULL);
}
