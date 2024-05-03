/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt.export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:06:03 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/03 11:08:46 by pborrull         ###   ########.fr       */
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

int	change_node(t_list **export, char *new_wrd)
{
	int	i;
	t_list	*temp;

	i = 0;
	temp = *export;
	while (temp)
	{
		while (temp->title[i] && new_wrd[i] && temp->title[i] == new_wrd[i]
			&& new_wrd[i] != '=')
			i++;
		if (new_wrd[i] && new_wrd[i] == '=' && !temp->title[i])
		{
			temp->def = ft_def(new_wrd);
			return (0);
		}
		temp = temp->next;
		i = 0;
	}
	return (1);
}

t_list	**ft_export(t_token **tokens, t_list **export, t_list **env)
{
	t_token	*temp;
	t_list	*temp2;
	int		i;

	i = 0;
	temp2 = *export;
	temp = *tokens;
	if (!(temp->next))
	{
		while (temp2)
		{
		//	printf("\nEl Def no se que es:%s\n", temp2->def);
			if (!temp2->def)
				printf("declare -x %s\n", temp2->title);
			else	
				printf("declare -x %s=\"%s\"\n", temp2->title, temp2->def);
			temp2 = temp2->next;
		}
	}
	while (temp->next)
	{
		temp = temp->next;
		while (temp->wrd[i] && temp->wrd[i] != '=')
			i++;
		if ((temp->wrd[i] && temp->wrd[i] != '=') || !temp->wrd[i])
		{
			if (change_node(export, temp->wrd))
				add_node(export, new_node(temp->wrd));
		}
		else
		{
			if (change_node(export, temp->wrd))
				add_node(export, new_node(temp->wrd));
			if (change_node(env, temp->wrd))
			{
				put_env(env, temp->wrd);
				add_node(env, new_node(temp->wrd));
			}
		}
	}
	return (export);
}
