/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:02:23 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/07 13:06:23 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_exp(t_list **export, char *wrd)
{
	t_list	*last;

	last = *export;
	while (last && (last->next))
		last = last->next;
	last->title = ft_title(wrd);
	last->def = ft_def(wrd);
	last->next = NULL;
}

void	put_env(t_list **env, char *wrd)
{
	t_list	*last;

	last = *env;
	while (last && (last->next))
		last = last->next;
	last->title = ft_title(wrd);
	last->def = ft_def(wrd);
	last->next = NULL;
}
