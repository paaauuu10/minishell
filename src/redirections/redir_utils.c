/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:15:28 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/22 12:57:19 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_redir_out(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    t_token *aux;
    int fd;
    
    temp = *tokens;
    while (temp)
    {
        if (ft_strcmp(temp->wrd, ">") != 0)
            break ;
        temp = temp->next;
    }
    temp = temp->next;
    fd = open(temp->wrd, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd == -1)
    {
        perror("open");
        return (-1); /*revisar*/
    }
    //dup2(fd, STDOUT_FILENO);
    temp = *tokens;
    while (ft_strcmp(temp->next->wrd, ">") == 0)
    {    
        /*hacer copia en t_token *aux de los nodos previos a ">"*/
        temp = temp->next;
    }
    temp->next = NULL;
    printf("TEST: %s\n", temp->wrd);
    ft_only_cmd(&temp, env, export, t_exec);
    close(fd);
    return (0);
}
