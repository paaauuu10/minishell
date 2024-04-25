/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:34:40 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/22 11:35:41 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_s;
	size_t	dst_s;
	size_t	j;

	i = 0;
	dst_s = ft_strlen(dst);
	src_s = ft_strlen(src);
	j = dst_s;
	if (size <= j)
		return (src_s + size);
	while (j < size - 1 && src[i])
	{
		dst[j] = src[i];
		i ++;
		j ++;
	}
	dst[j] = '\0';
	return (src_s + dst_s);
}
/*
int	main (void)
{
	char s[15] = "sdfsdfs";
	char d[30] = "ress";
	size_t t = 8;
	ft_strlcat(d, s, t);
	return (0);
}*/
