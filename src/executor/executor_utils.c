/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:09 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/06 16:53:41 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *ft_path(char *cmd, char **envp)
{
    char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
    paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
int    ft_exec(char *argv, char **envp)
{
    char **cmd;
    int i;
    char *path;

    i = -1;
    cmd = ft_split(argv, ' ');
    path = ft_path(cmd[0], envp);
    if (!path)
    {
        while(cmd[++i])
            free(cmd[i]);
        free(cmd);
        printf("Error\n");
        return (1);
    }
    if (execve(path, cmd, envp) == -1)
    {
        printf("Error 2\n");
        return (2);
    }
    return (0);
}