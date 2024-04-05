/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:51:23 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 13:32:21 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_hexa_u(unsigned int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len ++;
		n = n / 16;
	}
	return (len);
}

int	ft_printf_xx(int n)
{
	char			*r;
	int				len;
	int				i;
	unsigned int	un;

	un = n;
	len = ft_count_hexa_u(un);
	i = len;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (-1);
	if (un == 0)
	{
		free(r);
		return (ft_printchar('0'));
	}
	while (un > 0)
	{
		r[--len] = "0123456789ABCDEF"[un % 16];
		un = un / 16;
	}
	r[i] = '\0';
	len = ft_printf_s(r);
	free(r);
	return (len);
}
/*
int	main(void)
{
	int	str;
	str = 534243;
	ft_printf_xx(str);
	printf("\n%X", str);
	return (0);
}*/
