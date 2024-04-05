/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:21:03 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/26 15:33:33 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*r;

	j = 0;
	if (!s || start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s + start);
	if (i < len)
		len = i;
	r = malloc(len + 1);
	if (!r)
		return (NULL);
	while (j < len)
	{
		r[j] = s[start + j];
		j ++;
	}
	r[j] = '\0';
	return (r);
}
