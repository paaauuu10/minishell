/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:20:41 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/22 10:21:07 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int	main (void)
{
	char s[15] = "sdfsdfs";
	char d[30] ="";
	size_t t = 8;
	ft_strlcpy(d, s, t);
	return (0);
}*/
