/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt.export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:06:03 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/30 13:45:07 by pborrull         ###   ########.fr       */
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

int	change_node(t_list **export, char *new)
{
	int		i;
	t_list	*t;

	i = 0;
	t = *export;
	while (t)
	{
		while (new[i] && (new[i] != '=' || (new[i + 1] && new[i] == '+'
					&& new[i + 1] != '=')) && t->title[i] == new[i])
			i++;
		if (new[i] && new[i] == '=' && !t->title[i])
		{
			t->def = ft_def(new);
			return (0);
		}
		if (!new[i] && !t->title[i])
			return (0);
		if (new[i] && new[i + 1] && new[i] == '+'
			&& new[i + 1] == '=' && !t->title[i])
		{
			t->def = ft_strcat(t->def, ft_def(new),
					ft_strlen(t->def) + ft_strlen(new));
			return (0);
		}
		t = t->next;
		i = 0;
	}
	return (1);
}

static t_list	**ft_nxt(t_token *temp, int i, t_list **export, t_list **env)
{
	while (temp->next)
	{
		temp = temp->next;
		while (temp->wrd[i] && (temp->wrd[i] != '=' || (temp->wrd[i + 1]
					&& (temp->wrd[i] == '+' && temp->wrd[i + 1] != '='))))
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
			if (!temp2->def)
				printf("declare -x %s\n", temp2->title);
			else
				printf("declare -x %s=\"%s\"\n", temp2->title, temp2->def);
			temp2 = temp2->next;
		}
	}
	while (temp->next && temp->next->wrd[i] && (ft_isalnum(temp->next->wrd[i])
			|| temp->next->wrd[i] == '='))
		i++;
	if (temp->next && (temp->next->wrd[i] || ft_strcmp(temp->next->wrd, "=")
			|| !ft_isalpha(temp->next->wrd[0])) && temp->next->wrd[0] != '_')
	{
		write(2, " not a valid identifier\n", 24);
		ft_exit_status(1, 1);
		return (export);
	}
	i = 0;
	export = ft_nxt(temp, i, export, env);
	return (export);
}
