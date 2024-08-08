/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:58:34 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/08 11:10:21 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err(void)
{
	ft_print_error(" syntax error near unexpected token `newline'\n");
}

int	ft_syntax_2(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp)
	{
		if (temp->tok == 4)
		{
			if (temp->next == NULL)
			{
				ft_err();
				ft_exit_status(2, 1);
				return (1);
			}
			if (ft_syntax_2_aux(temp) == 1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_syntax_pipe(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	if (temp->tok == 2)
	{
		ft_exit_status(2, 1);
		ft_print_error(" syntax error near unexpected token `|'\n");
		return (1);
	}
	while (temp)
	{
		if (ft_syntax_pipe_aux(temp) == 1)
			return (1);
		temp = temp->next;
	}
	if (ft_syntax_2(tokens))
		return (1);
	return (0);
}

int	ft_syntax(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	if (!(*tokens))
		return (1);
	while (temp)
	{
		if (temp->tok == 3)
		{
			if (temp->next == NULL)
			{
				ft_err();
				ft_exit_status(2, 1);
				return (1);
			}
			if (syntax_aux(temp) == 1)
				return (1);
		}
		temp = temp->next;
	}
	if (ft_syntax_pipe(tokens))
		return (1);
	return (0);
}
