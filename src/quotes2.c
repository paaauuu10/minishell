/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:16:32 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/01 10:12:11 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes2_aux(t_parser *p, int temp, const char *s)
{
	while (s[temp + p->len] && (s[temp + p->len] != p->quote
			|| (p->open == 0 && p->quote != ' ')))
	{
		if ((s[temp + p->len] == '>' || s[temp + p->len] == '<'
				|| s[temp + p->len] == '|') && p->quote == ' ')
			break ;
		if ((s[temp + p->len] == '"' || s[temp + p->len] == '\'')
			&& (p->quote == ' ' || p->open == 0))
		{
			p->quote = s[temp + p->len++];
			p->open = 1;
			if (p->quote == '\'')
				p->exp = 1;
		}
		else
			p->len++;
		if (p->quote != ' ' && s[temp + p->len] && s[temp + p->len] == p->quote
			&& (s[temp + p->len] == '"' || s[temp + p->len] == '\''))
			p->open = 0;
		if (p->open == 0 && p->quote != ' ')
			p->quote = ' ';
	}
	return (temp);
}

int	ft_count_aux(const char *s, t_parser *p)
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
			return (1);
		}
		if (s[p->i] != ' ' && p->quote != ' ')
			return (2);
	}
	else
		ft_count2(s, p);
	return (0);
}

void	ft_quotes3_aux(t_parser *p, char **r, const char *s)
{
	if ((s[p->i] == '"' || s[p->i] == '\'')
		&& (p->quote == ' ' || p->open == 0))
	{
		p->quote = s[p->i];
		p->open = 1;
		if (s[p->i + 1] && (s[p->i + 1] == '|' || s[p->i + 1] == '>'
				|| s[p->i + 1] == '<') && s[p->i + 2] == p->quote)
			r[p->k][p->j++] = s[p->i++];
		else
			p->i++;
	}
	else
		r[p->k][p->j++] = s[p->i++];
	if (p->quote != ' ' && s[p->i] && s[p->i] == p->quote
		&& (s[p->i] == '"' || s[p->i] == '\''))
	{
		p->i++;
		p->open = 0;
	}
	if (p->open == 0 && p->quote != ' ')
		p->quote = ' ';
}
