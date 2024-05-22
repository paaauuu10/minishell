/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/21 14:37:08 by pborrull         ###   ########.fr       */
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
			if (s[i] == '"' || s[i] == '\'')
				i++;
			len++;
		}
		r[k] = (char *)malloc(sizeof(char) * (len + 1));
		if (!r[k])
			return (NULL);
		j = 0;
		while (s[i] && s[i] != quote)

			r[k][j++] = s[i++];
		r[k][j] = '\0';
		k++;
		if (s[i] == quote)
			i++;
	}
	r[k] = NULL;
	return (r);
}
/*
char	**ft_quotes(const char *s)
{
	char	**r;
	int		i;
	int		k;
	int		j;
	int		len;
	char	quote;

	i = 0;
	k = 0;
	r = (char **)malloc(sizeof(char *) * (ft_count(s) + 1));
	if (!r)
		return (NULL);
	while (s[i])
	{
		quote = ' ';
		if (s[i] == '"' || s[i] == '\'') 
		{
			quote = s[i++];
			if (s[i] == quote)
				i++;
			len = 0;
			while (s[i + len] && s[i + len] != quote)
				len++;
		}
		else 
		{
			len = 0;
			while (s[i + len] && s[i + len] != quote)//s[i + len] != ' ' && s[i + len] != '"' && s[i + len] != '\'') 
				len++;
		}
		r[k] = (char *)malloc(sizeof(char) * (len + 1));
		if (!r[k]) 
			return (NULL);
		j = 0;
		while (s[i] && (s[i] != quote))
		{
			if (s[i] == '"' || s[i] == '\'')
				i++;
			r[k][j++] = s[i++];
		}
		r[k][j] = '\0';
		k++;
		i++;
	}
	r[k] = NULL;
	return (r);
}*/
