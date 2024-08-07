/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:06:03 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/07 09:56:51 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_node_condi(char *new, t_list *t, int i)
{
	if (new[i] && new[i] == '=' && !t->title[i])
	{
		if (t->def)
			free(t->def); //revisar
		t->def = ft_def(new);
		return (0);
	}
	if (!new[i] && !t->title[i])
		return (0);
	if (new[i] && new[i + 1] && new[i] == '+'
		&& new[i + 1] == '=' && !t->title[i])
	{
		if (t->def)
			free(t->def); // revisar
		t->def = ft_strcat(t->def, ft_def(new),
				ft_strlen(t->def) + ft_strlen(new));
		return (0);
	}
	return (1);
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
		if (change_node_condi(new, t, i) == 0)
			return (0);
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
		i = 0;
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
				add_node(env, new_node(temp->wrd));
				//put_env(env, temp->wrd);
			}
		}
	}
	return (export);
}

static void	ft_print_exp(t_list *temp2)
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

t_list	**ft_export(t_token **tokens, t_list **export, t_list **env)
{
	t_token	*temp;
	t_list	*temp2;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp2 = *export;
	temp = *tokens;
	if (!(temp->next))
		ft_print_exp(temp2);
	while (temp->next && temp->next->wrd[i] && (ft_isalnum(temp->next->wrd[i])
			|| temp->next->wrd[i] == '='))
	{
		if (temp->next->wrd[i] == '=')
			k = 1;
		i++;
	}
	if (temp->next && ((temp->next->wrd[i] && k == 0) ||ft_strcmp(temp->next->wrd, "=")
			|| !ft_isalpha(temp->next->wrd[0])) && temp->next->wrd[0] != '_') //Revisar export HELLO="123 A-"
	{

		write(2, " not a valid identifier\n", 24);
		ft_exit_status(1, 1);
		return (export);
	}
	//i = 0;
	export = ft_nxt(temp, i, &temp2, env);
	return (export);
}
