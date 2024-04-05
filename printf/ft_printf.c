/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:00:38 by pborrull          #+#    #+#             */
/*   Updated: 2023/11/30 11:30:54 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(char c)
{
	int	i;

	i = write(1, &c, 1);
	return (i);
}

int	ft_wall_if(va_list list, char c)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_printchar((char)va_arg(list, int));
	else if (c == 's')
		i += ft_printf_s(va_arg(list, char *));
	else if (c == 'p')
		i += ft_printf_p(va_arg(list, unsigned long long));
	else if (c == 'd' || c == 'i')
		i += ft_printf_i(va_arg(list, int));
	else if (c == 'u')
		i += ft_printf_u(va_arg(list, unsigned int));
	else if (c == 'x')
		i += ft_printf_x(va_arg(list, int));
	else if (c == 'X')
		i += ft_printf_xx(va_arg(list, int));
	else if (c == '%')
		i += ft_printchar('%');
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		i;
	int		t;

	i = 0;
	t = 0;
	va_start(list, s);
	i = ft_while(s, i, t, list);
	va_end(list);
	return (i);
}
/*
int	main (void)
{
	printf("L'original torna:%i\n", printf("%d", 0));
	ft_printf("El meu :%i", ft_printf("%d", 0));
	return 0;
}*/
