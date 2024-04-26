/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:42 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/26 13:14:56 by pborrull         ###   ########.fr       */
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

char	*ft_str_list(t_token *temp, char *s2)
{
	int		i;

	i = 0;
	while (temp && temp->next)
	{
		while (s2[i] && (temp->wrd[i] == s2[i]))
		{
			i++;
			if ((!s2[i] || s2[i] == '$') && (temp->wrd[i] == '='))
			{	
				if (s2[i] == '$')
					return(ft_strcat(&temp->wrd[i + 1], ft_str_list(temp, &s2[i + 1]), 100));
				return (&temp->wrd[i + 1]);
			}
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

char	*ft_strcat(char *temp_wrd, char *exp, int i)
{
	char	*s;
	int		j;
	int		k;
//	int		l;

	k = 0;
	j = 0;
	if (!temp_wrd || !exp)
		return (NULL);
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		exit(1);
	while (temp_wrd[j] && temp_wrd[j] != '$')
	{
		s[j] = temp_wrd[j];
		j++;
	}/*
	l = j;
	if (temp_wrd[j])
	{*/
	while (exp[k])
		s[j++] = exp[k++];
/*	if (!temp_wrd[l])
	{
		s[j] = '\0';
	free(temp_wrd);
	}*/
	return (s);
}
