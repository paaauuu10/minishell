/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:31:00 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/15 14:41:43 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_output_redirect(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    int file;
    int save_file;
    t_token *temp;
    
    save_file = dup(STDOUT_FILENO);
    temp = *tokens;
    file = open(temp->next->next->next->wrd, O_WRONLY | O_CREAT, 0777);
    if (file == -1 )
        return (0); /*handle error*/
    dup2(file, STDOUT_FILENO);
    builtins(tokens, env, export);
    ft_exec(tokens, env, t_exec);
    close(file);
    dup2(save_file, STDOUT_FILENO);
    close(save_file);
    return (0);
}

int     redirections(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    
    temp = *tokens;
    while(temp)
    {
        if (ft_strcmp(temp->wrd, ">"))
        {
            ft_output_redirect(tokens, env, export, t_exec);
            return (0);
        }
        if (ft_strcmp(temp->wrd, "<"))
            return (0);
        if (ft_strcmp(temp->wrd, ">>"))
            return(0);
        if (ft_strcmp(temp->wrd, "<<"))
            return (0);
        temp = temp->next;
    }
    return (0);
}