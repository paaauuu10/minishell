/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:12:09 by pborrull          #+#    #+#             */
/*   Updated: 2023/09/27 11:10:18 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *d, const char *s, size_t n)
{
	size_t	i;
	size_t	j;

	if (*s == '\0' || s == d)
		return ((char *)d);
	i = 0;
	while (d[i] && i < n)
	{
		j = 0;
		while (s[j] != '\0' && d[i + j] != '\0'
			&& d[i + j] == s[j] && (j + i) < n)
			j++;
		if (s[j] == '\0')
			return ((char *)d + i);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	d[8] = "carmel";
	char	s[9] = "arm";

	ft_strnstr(s,d,6);
	return 0;
}
*/
