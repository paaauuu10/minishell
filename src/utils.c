/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:42 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/06 10:30:45 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen_r(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		count ++;
	return (count);
}

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

char	*ft_str_list2(t_list *temp2, char *s2)
{
	int		i;
	char	*a;
	char	*b;
	char	*z;
	int		s;

	i = 0;
	a = ft_itoa(ft_exit_status(0, 0));
	b = NULL;
	z = NULL;
	if (s2[i] && s2[i + 1] && s2[i + 2] && s2[i] == '$' && s2[i + 1] == '?')
	{
		s2 = ft_strcat(a, &s2[i + 2],
				(ft_strlen_r(a)+ ft_strlen_r(&s2[i + 2])));
		return (s2);
	}
	else if (s2[i] && s2[i + 1] && s2[i] == '$' && s2[i + 1] == '?')
	{
	//	s2 = ft_strcat(a, &s2[i + 2],
	//			(ft_strlen_r(a)+ ft_strlen_r(&s2[i + 2])));
		return (a);
	}

	free(a);
	while (s2[i + 1] && temp2->title[i] && (temp2->title[i] == s2[i + 1]))
	{
		i++;
		if ((!s2[i + 1] && !temp2->title[i]))
		{	
			z = ft_strdup(temp2->def);
			return (z);
		}
		if ((s2[i + 1] == '$' || s2[i + 1] == ' ') && !temp2->title[i])
		{
			z = ft_strdup(temp2->def);
			s = ft_strlen_r(z) + ft_strlen_r(&s2[i + 1]);
			b = ft_strcat(z, &s2[i + 1], s);
			return (b);
		}
	}
	return (NULL);
}

char	*ft_str_list(t_list **env, char *s2)
{
	int		i;
	t_list	*temp2;
	char	*s3;

	i = 0;
	temp2 = *env;
	while (temp2)
	{
		s3 = ft_str_list2(temp2, s2);
		if (s3)
			return (s3);
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
	free(temp_wrd);
	s[j] = '\0';
	return (s);
}
