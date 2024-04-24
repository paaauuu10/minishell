/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:01:28 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 13:06:51 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_count_hex(unsigned long n)
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

int	ft_printf_aux(unsigned long n)
{
	char			*r;
	unsigned int	len;
	int				i;

	len = ft_count_hex(n);
	i = len;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (-1);
	while (n >= 0 && len > 0)
	{
		r[--len] = "0123456789abcdef"[n % 16];
		n = n / 16;
	}
	r[i] = '\0';
	i = ft_printf_s(r);
	free(r);
	return (i);
}

int	ft_printf_p(unsigned long p)
{
	int	i;
	int	j;

	i = 0;
	j = write(1, "0x", 2);
	if (j < 0)
		return (-1);
	i += j;
	if (p == 0)
	{
		if (write(1, "0", 1) < 0)
			return (-1);
		i++;
	}
	else
	{
		if (ft_printf_aux(p) == -1)
			return (-1);
		i += ft_count_hex(p);
	}
	return (i);
}
/*
int	main(void)
{
	ft_printf_p(LONG_MIN);
	return (0);
}*/
