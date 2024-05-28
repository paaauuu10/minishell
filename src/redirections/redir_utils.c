/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:15:28 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/28 12:12:18 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_token_list(t_token **head) 
{
    t_token *current = *head;
    t_token *next;

    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

t_token	*ft_lstnew(char *word, int tokk)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->wrd = word;
    new_node->tok = tokk;
	new_node->next = NULL;
	return (new_node);
}


int ft_redir_out(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    t_token *aux_head;
    int fd;
    
    temp = *tokens;  
    while (temp)
    {
        if (ft_strcmp(temp->wrd, ">") != 0)
            break ;
        temp = temp->next;
    }
    if (temp && temp->next)
    {
        temp = temp->next;
        fd = open(temp->wrd, O_WRONLY | O_CREAT | O_TRUNC, 0664);
        if (fd == -1)
        {
            perror("open");
            return (-1); /*revisar*/
        }
    }
    temp = *tokens; 
    /*TENIM FILENAME I OBERT*/ 
    aux_head = ft_lstnew(temp->wrd, temp->tok);
    temp = temp->next;
    while (temp && ft_strcmp(temp->next->wrd, ">") != 0)
    {
        add_token(&aux_head, new_token(temp->wrd));
        temp = temp->next;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    if (aux_head)
    {
        ft_only_cmd(&aux_head, env, export, t_exec);
        free_token_list(&aux_head);
    }
    dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
    close(t_exec->d_pipe->original_stdout);
    //exit(1);
    return (0);
}

// int ft_redir_in(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
// {
//     t_token *temp;
    
//     temp = *tokens;
//     while (temp)
//     {
//         if (ft_strcmp(temp->wrd, ">") != 0)
//             break ;
//         temp = temp->next;
//     }
//     if (temp && temp->next)
//     {
//         temp = temp->next;
            
//     }   
// } 



