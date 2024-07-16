/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:58:34 by pbotargu          #+#    #+#             */
/*   Updated: 2024/07/16 12:12:13 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_2(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '>')
		{
			if (!(s[i + 1]))
			{	
				ft_print_error(" syntax error near unexpected token `newline'\n");
				ft_exit_status(2, 1);
				return (1);
			}
			if (s[i + 1] == '>' && ((!(s[i + 2]) || s[i + 2] == '>')))
			{
				if (s[i + 2] == '>')
					ft_print_error(" syntax error near unexpected token `>'\n");
				else
					ft_print_error (" syntax error near unexpected token `newline'\n");
				ft_exit_status(2, 1);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_syntax_pipe(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '|')
	{
		ft_exit_status(2, 1);
		ft_print_error(" syntax error near unexpected token `|'");
		return (1);
	}
	if (ft_syntax_2(s))
		return (1);
	return (0);
}

int	ft_syntax(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<')
		{
			if (!(s[i + 1]))
			{	
				ft_print_error(" syntax error near unexpected token `newline'\n");
				ft_exit_status(2, 1);
				return (1);
			}
			if (s[i + 1] == '<' && ((!(s[i + 2]) || s[i + 2] == '<')))
			{
				ft_print_error(" syntax error near unexpected token `newline'\n");
				ft_exit_status(2, 1);
				return (1);
			}
		}
		i++;
	}
	if (ft_syntax_pipe(s))
		return (1);
	return (0);

}
