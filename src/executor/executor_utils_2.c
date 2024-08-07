/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:15:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/07 15:29:44 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strl_v2(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_v2(char *s1, char *s2)
{
	char	*rtrn;
	int		i;

	i = 0;
	if (!s2)
		return (0);
	rtrn = (char *)malloc(sizeof(char) * (ft_strl_v2(s1) + ft_strl_v2(s2)+1));
	if (!rtrn)
		return (free(s1), NULL);
	if (s1)
	{
		while (s1[i])
		{
			rtrn[i] = s1[i];
			i++;
		}
	}
	while (*s2)
		rtrn[i++] = *s2++;
	rtrn[i] = '\0';
	free(s1);
	return (rtrn);
}

int	ft_env_lst_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**ft_copy_env(t_list **env)
{
	int		i;
	char	**new_env;
	t_list	*ref;

	i = ft_env_lst_size(*env);
	ref = *env;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ref)
	{
		new_env[i] = ft_strjoin(ref->title, "=");
		if (!new_env[i])
			exit(1);
		if (ref->def)
		{
			new_env[i] = ft_strjoin_v2(new_env[i], ref->def);
			if (!new_env[i])
				exit(1);
		}
		ref = ref->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
