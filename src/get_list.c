/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:09:51 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/16 15:40:33 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_title(char	*s)
{
	int		i;
	int		j;
	char	*r;

	i = 0;
	while (s[i] && (s[i] != '='))
		// || (s[i] == '+' && s[i + 1] && s[i + 1] != '=')))
		i++;
	if (i == 0)
	{
		perror("Is not a valid identifier");
		return (NULL);
	}
	if (s[i - 1] && s[i - 1] == '+')
		i--;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
		exit(1);
	j = i;
	i = 0;
	while (i < j)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	*ft_def(char	*s)
{
	int		i;
	int		j;
	char	*r;

	j = 0;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (NULL);
	while (s[i++])
		j++;
	r = (char *)malloc(sizeof(char) * (j));
	if (!r)
		exit(1);
	i = 0;
	j = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	while (s[i])
		r[j++] = s[i++];
	r[j] = '\0';
	return (r);
}

t_list	*new_node(char *s)
{
	t_list	*newtok;

	newtok = (t_list *)malloc(sizeof(t_list));
	if (!newtok)
	{
		perror("newtok");
		return(NULL);
	}
	newtok->title = ft_title(s);
	newtok->def = ft_def(s);
	if (!newtok->title)
		return (NULL);
	newtok->next = NULL;
	return (newtok);
}

t_list	**last_node(t_list **tokens)
{
	while (*tokens && (*tokens)->next)
		tokens = &((*tokens)->next);
	return (tokens);
}

void	add_node(t_list **env, t_list	*node)
{
	t_list	**last;

	last = last_node(env);
	if (!(*env))
		*env = node;
	else
		(*last)->next = node;
}
