/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:06:45 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 11:08:17 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_2_aux(t_token *temp)
{
	if (temp->next->tok == 4 && ((!(temp->next->next)) \
				|| temp->next->next->tok > 1))
	{
		if (!(temp->next->next))
			ft_err();
		else
			ft_print_error(" syntax error near unexpected token `>'\n");
		ft_exit_status(2, 1);
		return (1);
	}
	return (0);
}

int	ft_syntax_pipe_aux(t_token *temp)
{
	if (temp->tok == 2 && (!(temp->next)))
	{
		ft_print_error(" syntax error near unexpected token `|'\n");
		ft_exit_status(2, 1);
		return (1);
	}
	if (temp->tok == 2 && temp->next && temp->next->tok > 1)
	{
		if (temp->next->tok == 2)
			ft_print_error(" syntax error near unexpected token `|'\n");
		else
			ft_err();
		ft_exit_status(2, 1);
		return (1);
	}
	return (0);
}

int	syntax_aux(t_token *temp)
{
	if (temp->next->tok == 3 && ((!(temp->next->next)) \
		|| temp->next->next->tok == 3))
	{
		if (!(temp->next->next))
			ft_err();
		else
			ft_print_error(" syntax error near unexpected token `<'\n");
		ft_exit_status(2, 1);
		return (1);
	}
	return (0);
}
