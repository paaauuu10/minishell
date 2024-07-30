/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:46:27 by pborrull          #+#    #+#             */
/*   Updated: 2024/07/30 14:34:03 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	size_t	len;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	if (s1[0] == '"' || s1[0] == '\'')
	{
		i = 1;
		len--;
	}
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
		s2[j++] = s1[i++];
	s2[j] = '\0';
	return (&s2[0]);
}
/*
int	main(void)
{
	char	a[23] = "prova28";
	printf("%s", ft_strdup(a));
	return (0);
}*/
