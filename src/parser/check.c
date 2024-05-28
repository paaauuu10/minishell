/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:24:16 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/22 10:55:56 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_check_redirections_errors(char *str, int i, int *error)
{
    if (str[i] == '>')
    {
        if (ft_is_redirection(str, i))/*have to improve*/
            *error = printf("syntax error near unexpected token `>'\n");\
        else if (str[i + 1] == '>' && str[i + 2] == '>')
            *error = printf("syntax error near unexpected token '>>'\n");
    }
    else if (str[i] == '<')
	{
		if (ft_is_redirection(str, i))/*heve to improve*/
			*error = printf("syntax error near unexpected token `<'\n");
		else if (str[i + 1] == '<' && str[i + 2] == '<')
			*error = printf("syntax error near unexpected token '<<'\n");
	}
    else if (str[i] == '|')
	{
		if (check_rd(str, i))/*have to do*/
			*error = printf("syntax error near unexpected token `|'\n");
	}
}
int check_string(char *str)
{
    int i;
    int error;

    i = 0;
    error = 0;
    while (str[i])
    {
        ft_check_redirections_errors(str, i, &error);
        if (error != 0)
            return (1);
        i++;
    }
    return (0);
}

