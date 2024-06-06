/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:47:14 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/05 11:13:02 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

/*char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i ++;
	}
	s2[i] = '\0';
	return (&s2[0]);
}*/

int	ft_while(const char *s, int i, int t, va_list list)
{
	while (*s)
	{
		if (*s != '%')
		{
			if (ft_printchar(*s++) < 1)
				return (-1);
			i++;
		}
		else if (ft_strchr("cspdiuxX%", *(s + 1)))
		{
			++s;
			t = ft_wall_if(list, *s);
			if (t == -1)
				return (-1);
			else
				i += t;
			++s;
		}
		else
			return (-1);
	}
	return (i);
}
