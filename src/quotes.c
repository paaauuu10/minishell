/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/06 10:49:54 by pborrull         ###   ########.fr       */
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
		while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\''
			 && s[i] != '|' && s[i] != '<' && s[i] != '>')
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
		else if (s[i] && (s[i] == '|' || s[i] == '<' || s[i] == '>'))
		{
			if (s[i - 1] && s[i - 1] != '|' && s[i - 1] != '<' && s[i - 1] != '>')
				count++;
			if (s[i] == '>' && s[i + 1] == '>')
				i++;
			if (s[i] == '<' && s[i + 1] == '<')
				i++;
			i++;
		}
		else if (s[i])
		{
			while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '|' && s[i] != '<' && s[i] != '>')
				i++;
		}
		count++;
	}
	return (count);
}

char **ft_quotes(const char *s, t_list **env) {
	char **r;
	char quote;
	int i;
	int	j;
	int	k;
	int	len;

	r = (char **)malloc(sizeof(char *) * (ft_count(s) + 1));
	if (!r)
		return NULL;
	i = 0;
	k = 0;
	while (s[i])
	{
		quote = ' ';
		if (s[i] == '"' || s[i] == '\'')
			quote = s[i++];
		len = 0;
		while (s[i + len] && s[i + len] != quote && (((s[i + len] != '>' && s[i + len] != '<' && s[i + len] != '|')
			&& quote == ' ') || quote != ' '))
		{
			if ((s[i + len] == '"' || s[i + len] == '\'') && quote == ' ')
				len++;
			else
				len++;
		}
		while (s[i + len] && len == 0 && (s[i + len] == '>'
			|| s[i + len] == '<' || s[i + len] == '|'))
			len++;
		r[k] = (char *)malloc(sizeof(char) * (len + 1));
		if (!r[k])
			return NULL;
		j = 0;
		while (s[i] && s[i] != quote && (((s[i] != '>' && s[i] != '<' && s[i] != '|')
			&& quote == ' ') || quote != ' '))
		{
			if ((s[i] == '"' || s[i] == '\'') && quote == ' ')
				i++;
			else
				r[k][j++] = s[i++];
		}
		while (s[i] && j == 0 && ((s[i] == '>'
			|| s[i] == '<' || s[i] == '|') && quote == ' '))
			r[k][j++] = s[i++];
		r[k][j] = '\0';
		if (quote != '\'')
			r[k] = ft_expansor(env, r[k]);
		k++;
		if (s[i] == quote)
			i++;
	}
	r[k] = NULL;
	return r;
}
/*
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
}*/

