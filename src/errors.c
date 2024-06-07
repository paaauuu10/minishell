/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:28:59 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/07 12:29:07 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_errors(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i + 1] && s[i] == '<' && s[i + 1] == '|')
		{
			write (2, "Minishell: syntax error near unexpected token `|'\n", 50);
			ft_exit_status(2, 0);
			return (1);
		}
		if (s[i + 1] && s[i] == '|' && s[i + 1] == '|')
		{
			write (2, "Minishell: syntax error `||'\n", 29);
			ft_exit_status(2, 0);
			return (1);
		}
		if (s[i + 1] && s[i] == '&' && s[i + 1] == '&')
		{
			write (2, "Minishell: syntax error `&&'\n", 29);
			ft_exit_status(2, 0);
			return (1);
		}
		i++;
	}
	return (0);
}
