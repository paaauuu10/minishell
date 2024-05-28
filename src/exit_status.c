/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/exit_status.c
/*   Created: 2024/05/21 14:14:15 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/21 14:31:46 by pborrull         ###   ########.fr       */
=======
/*   Created: 2024/03/14 12:37:35 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/23 14:40:20 by pborrull         ###   ########.fr       */
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:blt_env.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD:src/exit_status.c
char	*ft_exit_status(int i, int j)
=======
int	ft_env(t_token	**env)
{
	int		i;
	t_token	*temp;

	temp = *env;
	i = 0;
	while (temp->next)
	{
		printf("%s\n", temp->wrd);
		temp = temp->next;
	}
	return (0);
}
/*int	ft_env(char	**env)
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:blt_env.c
{
	static char	*k;

<<<<<<< HEAD:src/exit_status.c
	if (j == 1)
		k = ft_itoa(i);
	return (k);
}
=======
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}*/
>>>>>>> 8b73d5e7bf7b0d94a37c6b66c27535a9d5bbf752:blt_env.c
