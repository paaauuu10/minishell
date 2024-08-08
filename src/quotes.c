/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/02 14:31:58 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count2(const char *s, t_parser *p)
{
	if (s[p->i] && (s[p->i] == '|' || s[p->i] == '<' || s[p->i] == '>'))
	{
		if (p->i > 0 && s[p->i - 1] && s[p->i - 1] != '|' && s[p->i - 1] != '<'
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
	int	j;

	if (!p)
		return ;
	p->i = 0;
	p->count = 0;
	p->quote = ' ';
	while (s[p->i])
	{
		j = ft_count_aux(s, p);
		if (j == 1)
			break ;
		else if (j == 2)
			continue ;
		p->count++;
	}
}

static char	*ft_quotes2(t_parser *p, char **r, const char *s)
{
	int	temp;

	temp = p->i;
	p->len = 0;
	p->exp = 0;
	temp = ft_quotes2_aux(p, temp, s);
	if (s[temp + p->len] && p->len == 0 && (s[temp + p->len] == '>'
			|| s[temp + p->len] == '<' || s[temp + p->len] == '|'))
		p->len++;
	r[p->k] = (char *)malloc(sizeof(char) * (p->len + 1));
	return (r[p->k]);
}

static void	ft_quotes3(t_parser *p, char **r, const char *s, t_list **env)
{
	p->j = 0;
	p->open = 0;
	while (s[p->i] && (s[p->i] != p->quote
			|| (p->open == 0 && p->quote != ' ')))
	{
		if ((s[p->i] == '>' || s[p->i] == '<'
				|| s[p->i] == '|') && p->quote == ' ')
			break ;
		ft_quotes3_aux(p, r, s);
	}
	if (s[p->i] && p->j == 0 && (s[p->i] == '>' || s[p->i] == '<'
			|| s[p->i] == '|'))
		r[p->k][p->j++] = s[p->i++];
	r[p->k][p->j] = '\0';
	if (p->exp != 1)
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
	ft_count(s, p);
	r = (char **)malloc(sizeof(char *) * (p->count + 2));
	if (!p || !r)
		return (NULL);
	p->i = 0;
	p->k = 0;
	p->open = 0;
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
	free(p);
	return (r);
}
