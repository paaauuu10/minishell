/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:15:28 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/22 14:49:54 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_redir_out(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    t_token *aux_head;
    int fd;
    
    aux_head = NULL;
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
    temp = *tokens;
    while (temp && ft_strcmp(temp->next->wrd, ">") == 0)
    {    
        /*COMO CREAR UNA LISTA NUEVA AUXILIAR QUE VAYA COPIANDO LOS NODOS DE TEMP*/
        t_token *new_node = malloc(sizeof(t_token));
        if (!new_node)
        {
            perror("malloc");
            // Manejar el error de asignación de memoria
        }
    
         // Copiamos el contenido del nodo actual de 'temp' al nuevo nodo
        new_node->wrd = strdup(temp->wrd);
        new_node->next = NULL;
    
        // Agregamos el nuevo nodo a la lista auxiliar
        if (!aux_head)
            aux_head = new_node; // Si es el primer nodo, lo asignamos como cabeza de la lista auxiliar
        else
        {
            // Si no es el primer nodo, lo agregamos al final de la lista auxiliar
            t_token *aux_last = aux_head;
            while (aux_last->next != NULL)
                aux_last = aux_last->next;
            aux_last->next = new_node;
        }
        temp = temp->next;
    }
    temp->next = NULL;
    while (aux_head)
    {
        printf("TEST: %s\n", aux_head->wrd);
        aux_head = aux_head->next;
    }
    dup2(fd, STDOUT_FILENO);
    /*if (aux_head)
        ft_only_cmd(&temp, env, export, t_exec);*/
    usleep(40000);/*change*/
    dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
    free(env);
    free(export);
    close(fd);
    return (0);
}


void free_list(t_token *head) {
    t_token *current = head;
    t_token *next;

    while (current != NULL) {
        next = current->next;
        free(current->wrd); // Liberamos la memoria del contenido del nodo
        free(current);       // Liberamos la memoria del nodo
        current = next;      // Avanzamos al siguiente nodo
    }
}


