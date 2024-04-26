/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:50:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/26 12:41:40 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*ft_expansor(char **envp, char *s)
{
	int		i;
	char	*r;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] && s[i++] == '$')
	{
		if (envp[0])
		{
			r = ft_str_matrix(envp, s);
			if (r)
			{
				if ((*r) != '_' && !ft_isalnum(*r++))
				{
					ft_printf("%s\n", r);
					return (r);
				}
			}
		}
	}
	return (NULL);
}*/
char	*ft_expansor(t_token **env, t_token **tokens)
{
	int		i;
	char	*r;
	int		j;
	int		k;
	t_token	*temp;
	t_token	*temp2;
	t_token	*prev;

	temp = *tokens;
	temp2 = *env;
	prev = temp;
	i = 0;
	j = 0;
	k = 0;
	while (temp)
	{
		while (temp->wrd[i] && temp->wrd[i] != '$')
			i++;
		if (temp->wrd[i] && temp->wrd[i++] == '$')
		{
			while (temp->wrd[j])
			{
				if (temp->wrd[j] == '$')
					k++;
				j++;
			}
			while (k-- > 0)
			{
				r = ft_str_list(temp2, &temp->wrd[i]);
				if (r)
				{
					if ((*r) != '_' && !ft_isalnum(*r++))
					{
						i += ft_strlen(r);
						temp->wrd = ft_strcat(temp->wrd, r, i);
					}
				}
				else
					prev = temp->next;
			}
		}
		i = 0;
		prev = temp;
		temp = temp->next;
	}
	return (NULL);
}
