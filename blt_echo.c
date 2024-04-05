/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:12 by pborrull          #+#    #+#             */
/*   Updated: 2024/03/14 12:52:45 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	ft_print_tokens(t_token **s)
//{
//}

int	ft_echo(t_token	**s)
{
	if ((*s)->wrd[0] == '\0')
		return (ft_printf("\n"));
	if ((*s)->wrd[0] == '-' && (*s)->wrd[1] == 'n' && !(*s)->wrd[2])
//		return (ft_print_tokens(s));
		return (0);
	else
	{
//		ft_print_tokens(s);
		return (ft_printf("\n"));
	}
}
