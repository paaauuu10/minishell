/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:05:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/07 09:48:52 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ft_unset_aux(t_list **export, t_list *temp, char *wrd, int i)
{
	if (!wrd[i] && !temp->title[i])
	{
		*export = temp->next;
		free(temp->title);
		free(temp);
		return (1);
	}
	return (0);
}*/

void	ft_unset(t_list **export, char *wrd)
{
    t_list *temp;
    t_list *prev;
    int i;

    i = 0;
    temp = *export;
    prev = NULL;

    while (temp)
    {
        while (temp->title[i] && wrd[i] && temp->title[i] == wrd[i])
            i++;
        if (!wrd[i] && !temp->title[i])
        {
            if (prev == NULL)
                *export = temp->next;
            else  // Eliminar un elemento intermedio o el último
                prev->next = temp->next;
      //      free(temp->title);
        //    free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
        i = 0;
    }
}

/*
void	ft_unset(t_list **export, char *wrd)
{
	t_list	*temp;
	t_list	*prev;
	int	i;

	i = 0;
	temp = *export;
	while (temp->title[i] && wrd[i] && temp->title[i] == wrd[i])
		i++;
	if (ft_unset_aux(export, temp, wrd, i))
		return ;*/
/*	if (!wrd[i] && !temp->title[i])
	{
		*export = temp->next;
		free(temp->title);
		free(temp);
		return ;
	}*/
/*	while (temp)
	{
		while (temp->title[i] && wrd[i] && temp->title[i] == wrd[i])
			i++;
		if (ft_unset_aux(export, temp, wrd, i))
			return ;
	*	if (!wrd[i] && !temp->title[i])
		{
			prev->next = temp->next;
			return ;
		}*/
	//	prev = temp;
/*		temp = temp->next;
		i = 0;
	}
}*/
