/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:54:05 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/22 13:31:52 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	ctr;

	str = (unsigned char *)s;
	ctr = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (str[i] == ctr)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
