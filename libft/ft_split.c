/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:11:50 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/03 09:20:32 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_len(char const *s, char c)
{
	unsigned long	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

char	**ft_aux2(char **r, char c, char const *s)
{
	size_t	j;
	size_t	len;

	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			r[j] = ft_substr(s - len, 0, len);
			if (!r[j])
			{
				while (j-- > 0)
					free(r[j]);
				return (NULL);
			}
			j++;
		}
		else
			s++;
	}
	r[j] = 0;
	return (r);
}

char	**ft_split(char const *s, char c)
{
	char	**r;

	if (!s)
		return (NULL);
	r = malloc(sizeof (char *) * (ft_len(s, c) + 1));
	if (!r)
		return (NULL);
	if (!ft_aux2(r, c, s))
	{
		free(r);
		return (NULL);
	}
	return (r);
}
/*
int	main(void)
{
	ft_split("para que sirve ", ' ');
	return (0);
}*/
/*
unsigned long	ft_auxx(char const *s, char c)
{
	unsigned long	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

void	ft_free_(char	**r, size_t j)
{
	while (j-- > 0)
		free(r[j]);
	free(r);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	size_t	j;
	size_t	len;

	j = 0;
	if (!s)
		return (NULL);
	r = malloc(sizeof (char *) * (ft_auxx(s, c) + 1));
	if (!r)
	{
		return (NULL);
	}
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			r[j] = ft_substr(s - len, 0, len);
			if (!r[j])
			{
				ft_free_(r, j);
				return (NULL);
			}
			j++;
		}
		else
			s++;
	}
	r[j] = 0;
	return (r);
}*/
