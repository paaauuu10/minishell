/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/14 12:04:08 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count2(const char *s, t_parser *p)
{
	if (s[p->i] && (s[p->i] == '|' || s[p->i] == '<' || s[p->i] == '>'))
	{
		if (s[p->i - 1] && s[p->i - 1] != '|' && s[p->i - 1] != '<'
			&& s[p->i - 1] != '>')
			p->count++;
		if (s[p->i] == '>' && s[p->i + 1] == '>')
			p->i++;
		if (s[p->i] == '<' && s[p->i + 1] == '<')
			p->i++;
		p->i++;
	}
	else if (s[p->i])
	{
		while (s[p->i] && s[p->i] != ' ' && s[p->i] != '"' && s[p->i] != '\''
			&& s[p->i] != '|' && s[p->i] != '<' && s[p->i] != '>')
			p->i++;
	}
}

static void	ft_count(const char *s, t_parser *p)
{
	p->i = 0;
	p->count = 0;
	p->quote = ' ';
	while (s[p->i])
	{
		while (s[p->i] && s[p->i] == ' ')
			p->i++;
		while (s[p->i] && s[p->i] != ' ' && s[p->i] != '"' && s[p->i] != '\''
			&& s[p->i] != '|' && s[p->i] != '<' && s[p->i] != '>')
			p->i++;
		if (s[p->i] && (s[p->i] == '"' || s[p->i] == '\''))
		{
			p->quote = s[p->i++];
			while (s[p->i] && s[p->i] != p->quote)
				p->i++;
			if (s[p->i] && s[p->i] == p->quote)
				p->i++;
			if (!s[p->i])
			{
				p->count++;
				break ;
			}
			if (s[p->i] != ' ' && p->quote != ' ')
				continue ;
		}
		else
			ft_count2(s, p);
		p->count++;
	}
}

static char	*ft_quotes2(t_parser *p, char **r, const char *s)
{
	int	len;
	int	temp;

	temp = p->i;
	len = 0;
	while (s[temp + len] && (s[temp + len] != p->quote
			|| (p->open == 0 && p->quote != ' ')))
	{
		if((s[temp + len] == '>' || s[temp + len] == '<'
				|| s[temp + len] == '|') && p->quote == ' ')
			break ;
		if ((s[temp + len] == '"' || s[temp + len] == '\'')
				&& (p->quote == ' ' || p->open == 0))
		{
				p->quote = s[temp++ + len];
				p->open = 1;
		}
		else
			len++;
		if (p->quote != ' ' && s[temp + len] && s[temp + len] == p->quote
				&& (s[temp + len] == '"' || s[temp + len] == '\''))
		{
			temp++;
			p->open = 0;
		}
	}
	if (s[temp + len] && len == 0 && (s[temp + len] == '>'
			|| s[temp + len] == '<' || s[temp + len] == '|'))
		len++;
	printf("Len de la paraula en posicio:%d, es:%d\n", p->k, len);
	r[p->k] = (char *)malloc(sizeof(char) * (len + 1));
	return (r[p->k]);
}

static void	ft_quotes3(t_parser *p, char **r, const char *s, t_list **env)
{
	p->j = 0;
	while (s[p->i] && (s[p->i] != p->quote || (p->open == 0 && p->quote != ' ')))
	{
		if((s[p->i] == '>' || s[p->i] == '<'
				|| s[p->i] == '|') && p->quote == ' ')
			break ;		
		if ((s[p->i] == '"' || s[p->i] == '\'') 
				&& (p->quote == ' ' || p->open == 0))
		{
			p->quote = s[p->i++];
			p->open = 1;
		}
		else
			r[p->k][p->j++] = s[p->i++];
		if (p->quote != ' ' && s[p->i] && s[p->i] == p->quote
				&& (s[p->i] == '"' || s[p->i] == '\''))
		{
			p->i++;
			p->open = 0;
		}
	}
	if (s[p->i] && p->j == 0 && (s[p->i] == '>' || s[p->i] == '<' || s[p->i] == '|'))
		r[p->k][p->j++] = s[p->i++];
	r[p->k][p->j] = '\0';
	if (p->quote != '\'')
		r[p->k] = ft_expansor(env, r[p->k]);
	p->k++;
	if (s[p->i] == p->quote)
		p->i++;
}

char	**ft_quotes(const char *s, t_list **env)
{
	char		**r;
	t_parser	*p;

	p = (t_parser *)malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->open = 0;
	ft_count(s, p);
	printf("Count is-> %d\n", p->count);
	r = (char **)malloc(sizeof(char *) * (p->count + 1));
	if (!r)
		return (NULL);
	p->i = 0;
	p->k = 0;
	while (s[p->i])
	{
		p->quote = ' ';
		while (s[p->i] == ' ')
			p->i++;
		r[p->k] = ft_quotes2(p, r, s);
		if (!r[p->k])
			return (NULL);
		ft_quotes3(p, r, s, env);
	}
	r[p->k] = NULL;
	return (r);
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
/*char	**ft_quotes(const char *s, t_list **env)
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
		while (s[i + len] && s[i + len] != quote && (((s[i + len] != '>'
						&& s[i + len] != '<' && s[i + len] != '|')
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
			return (NULL);
		j = 0;
		while (s[i] && s[i] != quote && (((s[i] != '>' && s[i] != '<'
						&& s[i] != '|') && quote == ' ') || quote != ' '))
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
	return (r);
}*/
