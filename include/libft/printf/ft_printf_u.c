/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:14:59 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 09:33:12 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		len ++;
		n = n / 10;
	}
	return (len);
}

char	ft_subitoa(int n, char *r)
{
	if (n == 0)
		r[0] = '0';
	return (r[0]);
}

char	*ft_uitoa(int n)
{
	char			*r;
	size_t			i;
	unsigned int	len;
	unsigned int	un;

	un = n;
	len = ft_len(un);
	i = len;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (0);
	r[0] = ft_subitoa(un, r);
	if (un == 0)
		r[0] = '0';
	while (un > 9)
	{
		r[--len] = '0' + (un % 10);
		un = un / 10;
	}
	len--;
	r[len] = 48 + un;
	r[i] = '\0';
	return (r);
}

int	ft_printf_u(int n)
{
	char			*r;
	unsigned int	result;

	r = ft_uitoa(n);
	if (r == 0)
		return (-1);
	result = ft_printf_s(r);
	free(r);
	return (result);
}
