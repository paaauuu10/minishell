/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:42 by pborrull          #+#    #+#             */
/*   Updated: 2024/03/20 09:38:27 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char	*s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

char	*ft_str_matrix(char **s1, char *s2)
{
	int	i;
	int	k;

	k = -1;
	i = 0;
	while (s1[++k])
	{
		while (s1[k][i] && s2[i + 1] && s1[k][i] == s2[i + 1])
		{
			i++;
			if (!s2[i + 1] && s1[k][i] == '=')
				return (&s1[k][i]);
		}	
		i = 0;
	}
	return (NULL);
}
int	ft_quote(const char	*s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			while (s[i + 1] && s[++i] != '\'')
				i++;
			if (!s[i])
			{
				perror("Single quote");
				exit(23);
			}
		}
		if (s[i] == '"')
		{
			while (s[i + 1] && s[++i] != '"')
				i++;
			if (!s[i])
			{
				perror("Doble quote");
				exit(24);
			}
		}
		i++;
	}
	return (0);
}

