/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/03 13:53:59 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_quotes(const char *s)
{
	char	**r;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	r = (char **)malloc(sizeof(char *) * 1000);
	r[k] = (char *)malloc(sizeof(char) * 1000);
	while (s[i])
	{
		if (s[i] != '"' && s[i] != '\'' && s[i] != ' ')
			r[k][j++] = s[i];
		else if (s[i] == ' ')
		{
			r[k++][j] = '\0';
			r[k] = (char *)malloc(sizeof(char) * 1000);
			j = 0;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
				r[k][j++] = s[i++];
			r[k++][j] = '\0';
			r[k] = (char *)malloc(sizeof(char) * 1000);
			j = 0;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				r[k][j++] = s[i++];
			r[k++][j] = '\0';
			r[k] = (char *)malloc(sizeof(char) * 1000);
			j = 0;
		}
		i++;
	}
	return (r);
}
