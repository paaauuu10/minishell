/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:46:27 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/21 13:02:08 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
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
}
/*
int	main(void)
{
	char	a[23] = "prova28";
	printf("%s", ft_strdup(a));
	return (0);
}*/
