/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:29:41 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 12:48:09 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_s(char *s)
{
	if (!s)
		return (ft_printf_s("(null)"));
	return (write(1, s, ft_strlen(s)));
}
/*
int	ft_printf_s(char *s)
{
	unsigned int	i;
	char			c;

	i = 0;
	if (!s)
	{
		i = write (1, "(null)", 6);
		return (i);
	}
	while (s[i])
	{
		c = s[i];
		if (ft_printchar(c) < 1)
			return (-1);
		i++;
	}
	return (i);
}

int	main(void)
{
	char	*str;
	str = "";
	ft_printf_s(str);
	printf("\n%s", str);
	return (0);
}*/
