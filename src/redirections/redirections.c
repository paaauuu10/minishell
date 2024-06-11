/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:09:41 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/11 16:03:31 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_redirect(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
    t_token *temp;
    char *filename;

    temp = *tokens;
    while (temp)
    {
        if (ft_strcmp(temp->wrd, ">"))
        {
            if (temp->next && temp->next->wrd[0] == '>')
	    	ft_redir_append(tokens, env, export, t_exec);
	    else
	    	ft_redir_out(tokens, env, export, t_exec);
            return (0); //revisar que ha de retornar
        }
        else if (ft_strcmp(temp->wrd, "<") == 1)
        {
            if (temp->next && temp->next->wrd[0] == '<')
	    {
	    	//printf("\nft_redir_here not implemented yet\n\n");
		ft_redir_here(tokens);
	    }
	    else
	    {
		//printf("\nRedir tokens not implemented yet\n\n");
		filename = (*tokens)->next->next->wrd;
		printf("%s\n", filename);
		ft_redir_in(filename, t_exec);
            }
	    return (0); //revisar que ha de retornar
        }
        temp = temp->next;
    }
    return (0); //revisar
}
