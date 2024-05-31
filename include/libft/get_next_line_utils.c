/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:41:04 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/31 11:53:48 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int d)
{
	int		i;
	char	c;

	i = 0;
	c = (char)d;
	if (!s)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		count ++;
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*r;
	size_t	i;
	size_t	j;
	size_t	cont;
	size_t	cont2;

	cont = 0;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	r = malloc((i + j + 1) * sizeof(char));
	if (!r)
		return (ft_free(&s1));
	while (i > cont)
	{
		r[cont] = s1[cont];
		cont++;
	}
	cont2 = 0;
	while ((i + j) > cont)
		r[cont++] = s2[cont2++];
	r[i + j] = '\0';
//	free(s1);
	return (r);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	csize;
	size_t	i;

	i = 0;
	csize = count * size;
	mem = malloc(csize);
	if (!mem)
		return (NULL);
	while ((i < csize) && csize > 0)
		mem[i++] = 0;
	return (mem);
}
