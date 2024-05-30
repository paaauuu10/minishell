/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:50:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/30 14:48:33 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expansor_while(t_token *temp, int i,  t_list **env)
{
	int		j;
	char	*r;

	j = 0;
	while (temp->wrd[i])
	{
		while (temp->wrd[i] && temp->wrd[i] != '$')
			i++;
		if (temp->wrd[i] && temp->wrd[i++] == '$')
		{
			r = ft_str_list(env, &temp->wrd[--i]);
			if (r)
			{
				if ((*r) != '_') //&& !ft_isalnum(*r))
				{
					j = i + ft_strlen(r);
					temp->wrd = ft_strcat(temp->wrd, r, j);
				}
				i++;
			}
			else
				return ;
		}
	}
}

char	*ft_expansor(t_list **env, char *s,  t_token *tokens)
{
	int		i;

	tokens->wrd = s;
	i = 0;
	if (ft_strcmp(tokens->wrd, "$?"))
			tokens->wrd = ft_exit_status(0, 0);
	ft_expansor_while(tokens, i, env);
	return (tokens->wrd);
}

/*
static void	ft_expansor_while(t_token *temp, t_token *prev, int i, t_list **env)
{
	int		j;
	char	*r;

	j = 0;
	while (temp->wrd[i])
	{
		while (temp->wrd[i] && temp->wrd[i] != '$')
			i++;
		if (temp->wrd[i] && temp->wrd[i++] == '$')
		{
			r = ft_str_list(env, &temp->wrd[--i]);
			if (r)
			{
				if ((*r) != '_') //&& !ft_isalnum(*r))
				{
					j = i + ft_strlen(r);
					temp->wrd = ft_strcat(temp->wrd, r, j);
				}
				i++;
			}
			else
				prev = temp->next;
		}
	}
}

char	*ft_expansor(t_list **env, t_token **tokens)
{
	int		i;
	t_token	*temp;
	t_token	*prev;

	temp = *tokens;
	prev = temp;
	i = 0;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, "$?"))
				temp->wrd = ft_exit_status(0, 0);
		ft_expansor_while(temp, prev, i, env);
		i = 0;
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}*/
