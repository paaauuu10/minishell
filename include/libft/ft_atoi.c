/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:29:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/14 09:13:37 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	r;

	r = 0;
	i = 0;
	signo = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45)
	{
		signo = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] && (str[i] < 48 || str[i] > 57))
		return (255);
	r *= signo;
	return (r);
}
/*
int	main(void)
{
	char  str[20] = "42";
	ft_atoi(str);
	return (0);
}*/
