/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:58:34 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/16 13:49:40 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char s)
{
	if (s == '\n')
		return (1);
	return (0);
}

int	ft_syntax_2(t_token **tokens)
{
	t_token *temp;

	temp = *tokens;
	while (temp)
	{
		if (temp->tok == 4)
		{
			if (temp->next == NULL)
			{	
				ft_print_error(" syntax error near unexpected token `newline'\n");
				ft_exit_status(2, 1);
				return (1);
			}
			if (temp->next->tok == 4 && ((!(temp->next->next)) || temp->next->next->tok != 0))
			{
				if (!(temp->next->next))
					ft_print_error(" syntax error near unexpected token `newline'\n");
				else
					ft_print_error(" syntax error near unexpected token `>'\n");
				ft_exit_status(2, 1);
				return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_syntax_pipe(t_token **tokens)
{
	t_token *temp;

	temp = *tokens;
	if (temp->tok == 2)
	{
		ft_exit_status(2, 1);
		ft_print_error(" syntax error near unexpected token `|'\n");
		return (1);
	}
	while (temp)
	{
		if (temp->tok == 2 && temp->next->tok != 0)
		{
			if (temp->next->tok == 2)
				ft_print_error(" syntax error near unexpected token `|'\n");
			else
				ft_print_error(" syntax error near unexpected token `newline'\n");
			ft_exit_status(2, 1);
			return (1);
		}
		temp = temp->next;
	}
	if (ft_syntax_2(tokens))
		return (1);
	return (0);
}

int	ft_syntax(t_token **tokens)
{
	t_token *temp;

	temp = *tokens;
	if (!(*tokens))
		return (1);
	while (temp)
	{
		if (temp->tok == 3)
		{
			if (temp->next == NULL)
			{	
				ft_print_error(" syntax error near unexpected token `newline'\n");
				ft_exit_status(2, 1);
				return (1);
			}
			if (temp->next->tok == 3 && ((!(temp->next->next)) || temp->next->next->tok == 3))
			{
				if (!(temp->next->next))
					ft_print_error(" syntax error near unexpected token `newline'\n");
				else
					ft_print_error(" syntax error near unexpected token `<'\n");
				ft_exit_status(2, 1);
				return (1);
			}
		}
		temp = temp->next;
	}
	if (ft_syntax_pipe(tokens))
		return (1);
	return (0);

}
