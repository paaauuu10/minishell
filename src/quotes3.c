/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:45:15 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/08 10:50:35 by pborrull         ###   ########.fr       */
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

char	*ft_str_list2_part2(t_list *temp2, char *s2, int i)
{
	char	*b;
	char	*z;
	int		s;

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

char	*ft_str_list2(t_list *temp2, char *s2)
{
	int		i;
	char	*a;

	i = 0;
	a = ft_itoa(ft_exit_status(0, 0));
	if (s2[i] && s2[i + 1] && s2[i + 2] && s2[i] == '$' && s2[i + 1] == '?')
	{
		s2 = ft_strcat(a, &s2[i + 2],
				(ft_strlen_r(a) + ft_strlen_r(&s2[i + 2])));
		return (s2);
	}
	else if (s2[i] && s2[i + 1] && s2[i] == '$' && s2[i + 1] == '?')
		return (a);
	free(a);
	return (ft_str_list2_part2(temp2, s2, i));
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
			if (s2[++i])
				return (s2);
			else
				return (NULL);
		}
	}
	return (NULL);
}
