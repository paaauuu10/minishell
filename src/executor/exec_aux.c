/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:24:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/06 12:59:13 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_free_strjoin(char *s1, char *s2)
{
	char	*rtrn;
	int		i;

	i = 0;
	if (!s2)
		return (0);
	rtrn = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+1));
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

int	ft_list_size_tlist(t_list *list)
{
	int	 i;
	
	i = 0;
	while(list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char **ft_get_env(t_list **env)
{
	char	**ret_env;
	t_list	*aux;
	int	len;
	int	i;

	aux = *env;
	len = ft_list_size_tlist(*env);
	ret_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret_env)
	{
		perror("Malloc\n"); //revisar com tractarem aixo
		return (0);
	}
	i = 0;
	while (aux)
	{
		ret_env[i] = ft_strjoin(aux->title, "=");
		if (!ret_env[i])
		{
			perror("Malloc\n"); //revisar com tractem error;
			return (0);
		}
		if (aux->def)
		{
			ret_env[i] = ft_free_strjoin(ret_env[i], aux->def);
			if (!ret_env[i])
			{
				perror("Malloc\n"); //revisar com tractem l'error
				return (0);
			}
		}
		aux = aux->next;
		i++;
	}
	i++;
	ret_env[i] = NULL;
	i = 0;
	while (ret_env[i])
	{
		printf("%s\n", ret_env[i]);
		i++;
	}
	return (ret_env);
}
