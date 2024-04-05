/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:22:33 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/25 12:48:15 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (i < n && n != 0)
	{
		d[i] = s[i];
		i ++;
	}
	return (dst);
}
/*
int	main(void)
{
	char	src[23] = "owoweebfob";
	char	dst[18] = "sdfkbkbjbd";
	ft_memcpy(dst, src, 8);
	return 0;
}*/
