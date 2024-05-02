/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:06:03 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/30 14:45:27 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_exp(t_token **export, char *wrd)
{
	t_token	*last;

	last = *export;
	while (last && last->next)
			last = last->next;
	last->wrd = wrd;
	last->next = NULL;
}

void	put_env(t_token **env, char *wrd)
{
	t_token	*last;

	last = *env;
	while (last && (last->next))
		last = last->next;
	last->wrd = wrd;
	last->next = NULL;
}

int	change_tok(t_token **export, char *new_wrd)
{
	int	i;
	t_token	*temp;

	i = 0;
	temp = *export;
	while (temp)
	{
		while (temp->wrd[i] && new_wrd[i] && temp->wrd[i] == new_wrd[i]
			&& new_wrd[i] != '=')
			i++;
		if ((new_wrd[i] && new_wrd[i] == '=' && temp->wrd[i] == new_wrd[i])
			|| !temp->wrd[i])
		{
			temp->wrd = new_wrd;
			return (0);
		}
		temp = temp->next;
		i = 0;
	}
	return (1);
}

t_token	**ft_export(t_token **tokens, t_token **export, t_token **env)
{
	t_token	*temp;
	t_token	*temp2;
	int		i;

	i = 0;
	temp2 = *export;
	temp = *tokens;
	if (!(temp->next))
	{
		while (temp2)
		{
			printf("declare -x %s\n", temp2->wrd);
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
			if (change_tok(export, temp->wrd))
				add_token(export, new_token(temp->wrd));
		}
		else
		{
			if (change_tok(export, temp->wrd))
				add_token(export, new_token(temp->wrd));
			if (change_tok(env, temp->wrd))
			{
				put_env(env, temp->wrd);
				add_token(env, new_token(temp->wrd));
			}
		}
	}
	return (export);
}
