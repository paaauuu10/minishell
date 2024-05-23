/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/23 22:09:35 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(const char *s)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
			i++;
		if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (!s[i])
				break ;
			if (s[i] == quote)
				i++;
		}
		count++;
	}
	return (count);
}

char	**ft_quotes(const char *s)
{
	char	**r;
	char	quote;
	int		i;
	int		j;
	int		k;
	int		len;

	r = (char **)malloc(sizeof(char *) * (ft_count(s) + 1));
	if (!r)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		quote = ' ';
		if (s[i] == '"' || s[i] == '\'')
			quote = s[i++];
		len = 0;
		while (s[i + len] && s[i + len] != quote)
		{
			if ((s[i] == '"' || s[i] == '\'') && quote == ' ')
				i++;
			len++;
		}
		r[k] = (char *)malloc(sizeof(char) * (len + 1));
		if (!r[k])
			return (NULL);
		j = 0;
		while (s[i] && s[i] != quote)
		{
			if ((s[i] == '"' || s[i] == '\'') && quote == ' ')
				i++;
			else
				r[k][j++] = s[i++];
		}
		r[k][j] = '\0';
		k++;
		if (s[i] == quote)
			i++;
	}
	r[k] = NULL;
	return (r);
}
