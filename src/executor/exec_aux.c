/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:24:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/06 11:00:33 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell"

int	ft_list_size(t_list *list)
{
	int	 i;
	
	i = 0;
	while(lst)
	{
		lst = lst->next;
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
	len = ft_list_size(*env);
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
		if (aux->)
	}

}
