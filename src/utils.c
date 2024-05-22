/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:42 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/22 09:11:12 by pborrull         ###   ########.fr       */
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


char	*ft_str_list(t_list **env, char *s2)
{
	int		i;
	t_list	*temp2;

	temp2 = *env;
	i = 0;
	while (temp2)
	{
		while (s2[i + 1] && temp2->title[i] && (temp2->title[i] == s2[i + 1]))
		{
			i++;
			if ((!s2[i + 1] || s2[i + 1] == '$') && !temp2->title[i])
			{
				if (s2[i + 1] == '$')
					return (ft_strcat(temp2->def, &s2[i + 1],
							(ft_strlen(temp2->def) + ft_strlen(s2) - i)));
				return (temp2->def);
			}
		}
		i = 0;
		if (temp2->next)
			temp2 = temp2->next;
		else
		{
			while (s2[i + 1] && s2[i + 1] != '$')
				i++;
			if (s2[i])
				return (s2);
			else
				return (NULL);
		}
	}
	return (NULL);
}

int	ft_quote_error(const char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			i += 1;
			while (s[i] && s[i] != quote)
				i++;
			if (!s[i])
			{
				if (quote == '\'')
					perror("Single quote unfinished");
				else
					perror("Double quote unfinished");
				exit(1);
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
	}
	while (exp[k])
		s[j++] = exp[k++];
	s[j] = '\0';
	return (s);
}
