/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:14:56 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 12:58:55 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_num_count(int n)
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

static char	*ft_itoa(int n)
{
	char			*r;
	size_t			i;
	unsigned int	len;

	len = ft_num_count(n);
	i = len;
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (0);
	if (n < 0)
	{
		n *= -1;
		r[0] = 45;
	}
	while (n > 9)
	{
		r[--len] = '0' + (n % 10);
		n = n / 10;
	}
	len--;
	r[len] = 48 + n;
	r[i] = '\0';
	return (r);
}

int	ft_printf_i(int n)
{
	char			*r;
	unsigned int	i;

	r = ft_itoa(n);
	if (r == 0)
		return (-1);
	i = ft_printf_s(r);
	free(r);
	return (i);
}
/*
int	main(void)
{
	int	str;
	str = 0;
	ft_printf_i(str);
	printf("\n%i", str);
	return (0);
}*/
