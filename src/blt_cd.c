/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:33:55 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/06 11:12:13 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_env(char *oldpwd, t_list **env)
{
	t_list	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->title, "PWD"))
		{	
			if (temp->def) //potser no cal if
				free(temp->def); // calia fer free
			temp->def = getcwd(NULL, 0);
		}
		temp = temp->next;
	}
	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->title, "OLDPWD"))
		{	
			if (temp->def) //potser no cal if
				free(temp->def); // calia fer free
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

static char	*ft_cd_condi(t_list **env, char *newpwd, t_token **tokens)
{
	if (*tokens && (*tokens)->next && (*tokens)->next->next)
	{
		write(2, "Minishell: cd: too many arguments\n", 34);
		ft_exit_status(1, 1);
		return (NULL);
	}
	if (!(*tokens)->next)
	{
		newpwd = ft_go_home(env);
		if (!newpwd)
		{
			write(2, "Minishell: cd: HOME not set\n", 28);
			ft_exit_status(1, 1);
			return (NULL);
		}
	}
	else
		newpwd = (*tokens)->next->wrd;
	return (newpwd);
}

int	ft_cd(t_token	**tokens, t_list **export, t_list **env)
{
	char	*oldpwd;
	char	*newpwd;

	newpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exit(43);
	newpwd = ft_cd_condi(env, newpwd, tokens);
	if (!newpwd)
	{	
		free(oldpwd);
		return (1);
	}
	if (chdir(newpwd))
	{
		write(2, "Minishell: ", 11);
		free(oldpwd);
		perror(newpwd);
		ft_exit_status(1, 1);
		return (1);
	}
	ft_change_env(oldpwd, env);
	ft_change_env(oldpwd, export);
	free(oldpwd);
	return (0);
}
