/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/07/31 15:07:04 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_exit_status(int i, int j)
{
	static char	*k;

	if (j == 1)
	{
	/*	if (k != NULL)
		{
			free(k);
			k = NULL;
		}*/
		k = ft_itoa(i);
	}
	return (k);
}
