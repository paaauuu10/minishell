/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:31:34 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/19 13:28:55 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t j)
{
	int				i;
	int				x;
	unsigned char	*s;

	x = (int) j;
	s = (unsigned char *) ptr;
	i = 0;
	while ((i < x) && x > 0)
	{
		s[i] = c;
		i ++;
	}
	return (ptr);
}
/*
int	main(void)
{
	int	array[4];
	ft_memset(array, 5, 3);
	return (0);
}*/
