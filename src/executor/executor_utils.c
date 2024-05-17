/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:09 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/17 13:00:56 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*char    *ft_path(char *cmd, char **envp)
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
	if (!cmd[0])
		return(0);
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
}*/

// This function counts and returns the number of nodes in a linked list of type t_token.
// It iterates through the list until it reaches the end (when token is NULL or token->wrd is NULL).
// For each node, it increments the counter i.

int	ft_list_size(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->wrd != NULL)
	{
		token = token->next;
		i++;
	}
	return (i);
}

// This function searches the env list for the PATH environment variable.
// Once found, it splits the PATH variable into an array of strings using ':' as a delimiter.
// It also constructs the command string by prepending '/' to the token's word.
// Returns 127 if PATH is not found, and 1 in case of errors in splitting or string concatenation.

int	ft_path(t_token **tokens, t_list **env, t_executor **t_exec)
{
	while (ft_strncmp("PATH", (*env)->title, 4) != 0)
	{
		*env = (*env)->next;
		if (!env)
		{
			/*ft_error_cmd((*tokens)->wrd, 2);*/ /*hem de tractar l'error perque doni una señal a la terminal*/
			return (127);/*127 indica que un comando no se encuentra o no se puede ejecutar*/
		}
	}
	(*t_exec)->path = ft_split((*env)->def, ':');
	if (!(*t_exec)->path)
		return (1); /*revisar com tractem l'error, aixi segur que no*/
	(*t_exec)->cmd = ft_strjoin("/", (*tokens)->wrd);
	if (!(*t_exec)->cmd)
		return (1); /*revisar com tractem l'error, aixi segur que no*/
	return (0);
}

// This function attempts to construct absolute paths for the command and checks if they are executable.
// It iterates over the array of PATH directories, concatenates each with the command, and uses access() to check executability.
// If an executable command is found, it returns 1; otherwise, it returns 0.

int	ft_exec_cmd(t_executor **t_exec)
{
	int	i;

	i = 0;
	while ((*t_exec)->path[i])
	{
		(*t_exec)->absolute_path = ft_strjoin((*t_exec)->path[i], (*t_exec)->cmd);
		if (!(*t_exec)->cmd)
			return (0); /*REVISAR COM FEM EXIT I QUIN VALOR */
		if (access((*t_exec)->absolute_path, X_OK) == 0)
			return (1);
		free((*t_exec)->absolute_path);
		i++;
	}
	/*hem de tractar si surt dek bucle, vol dir que no ha trobat*/
	return (0);
}

// This function coordinates the execution of a command.
// Steps:
// 1. Calls ft_path to obtain command paths and construct the command string.
// 2. Allocates memory for cmd_argv, an array of strings for command arguments.
// 3. Fills cmd_argv with the token words.
// 4. Calls ft_exec_cmd to find and validate an executable path.
// 5. If an executable path is found, calls execve to execute the command.
// Returns 1 on error and 0 if the command cannot be found or executed.

int	ft_exec(t_token **tokens, t_list **env, t_executor *t_exec)
{
	int	i;

	i = 0;
	if (ft_path(tokens, env, &t_exec) != 0)
		return (1);
	t_exec->cmd_argv = (char **)malloc(sizeof(char *) * (ft_list_size(*tokens) + 1));
	if (!t_exec->cmd_argv)
		return (1); /*revisar com tractem l'error, aixi segur que no*/
	t_exec->cmd_argv[ft_list_size(*tokens)] = NULL;
	while (*tokens)
	{
		t_exec->cmd_argv[i] = ft_strdup((*tokens)->wrd);
		if (!t_exec->cmd[i])
			return (1); /*revisar com tractem l'error, aixi segur que no*/
		*tokens = (*tokens)->next;
		i++;
	}
	if (ft_exec_cmd(&t_exec))
		execve(t_exec->absolute_path, t_exec->cmd_argv, t_exec->new_envp);
	return (0); /*127 indica que un comando no se encuentra o no se puede ejecutar*/
}

// int ft_exec(t_token **tokens, t_list **env, t_executor *t_exec)
// {
//     int i = 0;
//     if (ft_path(tokens, env, &t_exec) != 0)
//         return (1);
    
//     // Asignación de memoria para cmd_argv
//     t_exec->cmd_argv = (char **)malloc(sizeof(char *) * (ft_list_size(*tokens) + 1));
//     if (!t_exec->cmd_argv) {
//         // Liberar memoria de t_exec->path si se asignó
//         if (t_exec->path)
//             free(t_exec->path);
//         return (1);
//     }
//     t_exec->cmd_argv[ft_list_size(*tokens)] = NULL;

//     // Utilizar un puntero temporal para no modificar la lista original de tokens
//     t_token *temp_token = *tokens;
//     while (temp_token)
//     {
//         t_exec->cmd_argv[i] = ft_strdup(temp_token->wrd);
//         if (!t_exec->cmd_argv[i]) {
//             // Liberar memoria de cmd_argv si la asignación de strdup falló
//             free(t_exec->cmd_argv);
//             // Liberar memoria de t_exec->path si se asignó
//             if (t_exec->path)
//                 free(t_exec->path);
//             return (1);
//         }
//         temp_token = temp_token->next;
//         i++;
//     }
    
//     if (ft_exec_cmd(&t_exec))
//         execve(t_exec->absolute_path, t_exec->cmd_argv, t_exec->new_envp);
    
//     // Liberar memoria de t_exec->path si se asignó
//     if (t_exec->path)
//         free(t_exec->path);
    
//     // Liberar memoria de cmd_argv
//     free(t_exec->cmd_argv);
    
//     return (0);
// }

