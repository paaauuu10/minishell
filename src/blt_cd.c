/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:33:55 by pborrull          #+#    #+#             */
/*   Updated: 2024/05/03 12:09:47 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_env(char *oldpwd, char *newpwd, t_list **env)
{
	t_list	*temp;
	int		i;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->title, "PWD"))
		{
			i = ft_strlen(newpwd) + 4;
			temp->def = newpwd;
		}
		temp = temp->next;
	}
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->title, "OLDPWD"))
		{
			i = ft_strlen(oldpwd) + 7;
			temp->def = oldpwd;
		}
		temp = temp->next;
	}
}

char	*ft_go_home(t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->title, "HOME"))
			return (temp->def);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_cd(t_token	**tokens, t_list **export, t_list	**env)
{
	char	*oldpwd;
	char	*newpwd;

	newpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exit(43);
	if (!(*tokens)->next)
	{
		newpwd = ft_go_home(env);
		if (!newpwd)
		{
			write(2, "Minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		newpwd = (*tokens)->next->wrd;
	if (chdir(newpwd))
	{
		write(2, "Minishell: ", 11);
		perror(newpwd);
		return (1);
	}
	ft_change_env(oldpwd, newpwd, env);
	ft_change_env(oldpwd, newpwd, export);
	return (0);
}
