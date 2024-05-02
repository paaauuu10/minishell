/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:42 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/30 14:45:10 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
/*
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
}*/
char	*ft_str_list(t_token *temp, char *s2)
{
	int		i;

	i = 0;
	while (temp && temp->next)
	{
		while (s2[i + 1] && (temp->wrd[i] == s2[i + 1]))
		{
			i++;
			if (!s2[i + 1] && (temp->wrd[i] == '='))
				return (&temp->wrd[i]);
		}
		i = 0;
		temp = temp->next;
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
			i += 1;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i])
			{
				perror("Single quote");
				exit(23);
			}
		}
		if (s[i] == '"')
		{
			i += 1;
			while (s[i] && s[i] != '"')
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
