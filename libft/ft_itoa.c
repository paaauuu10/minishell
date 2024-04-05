/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:29:03 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/29 11:03:57 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_len(int n)
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
	if (n < 0)
		r[0] = 45 ;
	return (r[0]);
}

char	*ft_itoa(int n)
{
	char			*r;
	size_t			i;
	unsigned int	len;

	len = ft_len(n);
	i = len;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (0);
	r[0] = ft_subitoa(n, r);
	if (n == 0)
		r[0] = '0';
	if (n < 0)
		n *= -1;
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
/*
int main(void)
{
	char * res = ft_itoa(-2147483648);
	printf("El nombre es: %s", res);
	return (0);
}*/
