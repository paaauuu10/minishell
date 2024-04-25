/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:55:20 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/25 12:50:57 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n && n != 0)
		{
			d[i] = s[i];
			i ++;
		}
	}
	return (dst);
}
/*
int	main(void)
{
	char	src[23] = "lorem ipum dolor sit a";
	char	dst[18] = "sdfkbkbjbd";
	ft_memmove(dst, src, 8);

	return 0;
}*/
