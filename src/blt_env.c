/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/blt_env.c
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/09 09:08:42 by pborrull         ###   ########.fr       */
=======
/*   Created: 2024/03/15 10:50:06 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/23 15:40:33 by pborrull         ###   ########.fr       */
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:expansor.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
<<<<<<< HEAD:src/blt_env.c

t_list	**env_list(char **envp)
=======
/*
char	*ft_expansor(char **envp, char *s)
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:expansor.c
{
	t_list	**env;
	int		i;

	i = 0;
	env = (t_list **)malloc(sizeof(t_list *));
	if (!env)
		return (NULL);
	while (envp[i])
		add_node(env, new_node(envp[i++]));
	return (env);
}

int	ft_env(t_list	**env)
{
	int		i;
	t_list	*temp;

	temp = *env;
	i = 0;
	while (temp->next)
	{
		printf("%s=%s\n", temp->title, temp->def);
		temp = temp->next;
	}
<<<<<<< HEAD:src/blt_env.c
	return (0);
=======
	return (NULL);
}*/
char	*ft_expansor(t_token **env, t_token **tokens)
{
	int		i;
	char	*r;
	t_token	*temp;
	t_token	*temp2;
	t_token	*prev;

	temp = *tokens;
	temp2 = *env;
	prev = temp;
	i = 0;
	while (temp)
	{
		while (temp->wrd[i] && temp->wrd[i] != '$')
			i++;
		if (temp->wrd[i] && temp->wrd[i++] == '$')
		{
			while (temp2)
			{
				r = ft_str_list(temp2, temp->wrd);
				if (r)
				{
					if ((*r) != '_' && !ft_isalnum(*r++))
					{
						temp->wrd = ft_strdup(r);
						//temp2->wrd = r;
					//	printf("Es:%s\n", temp2->wrd);
						return (temp->wrd);
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
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:expansor.c
}
