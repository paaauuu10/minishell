/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:47:47 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/07 14:20:00 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_is_builtin(t_token **tokens)
{
    if (!*tokens)
        return (0);
   
    if (ft_strcmp((*tokens)->wrd, "echo") || \
    ft_strcmp((*tokens)->wrd, "env") || \
	ft_strcmp((*tokens)->wrd, "pwd") || \
	ft_strcmp((*tokens)->wrd, "exit") || \
    ft_strcmp((*tokens)->wrd, "export") || \
	ft_strcmp((*tokens)->wrd, "unset"))
        return (1);
    return (0);
}   
