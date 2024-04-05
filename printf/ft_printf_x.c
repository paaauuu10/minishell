/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:25:18 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 09:33:58 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned long n)
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

int	ft_printf_x(unsigned int n)
{
	char			*r;
	int				len;
	int				i;
	unsigned int	un;

	un = n;
	len = ft_len(un);
	i = len;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (-1);
	else if (un == 0)
	{
		free(r);
		return (ft_printchar('0'));
	}
	while (un > 0 && len > 0)
	{
		r[--len] = "0123456789abcdef"[un % 16];
		un = un / 16;
	}
	r[i] = '\0';
	len = ft_printf_s(r);
	free(r);
	return (len);
}
/*
void print_x(unsined long int n, int base)
{
	if (n >= base)
		print_x(n / base);
	write(1, &"0123456789abcdef"[n % base], 1);i
}*/
/*
int	main(void)
{
	int	str;
	str = -5346543;
	ft_printf_x(str);
	printf("\n%x", str);
	return (0);
}*/
