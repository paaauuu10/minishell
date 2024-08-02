/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:02:09 by pbotargu          #+#    #+#             */
/*   Updated: 2024/08/02 10:23:04 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*******************************************
				cal revisar
********************************************/

/*size_t	ft_strlen_s(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_s(char *s1, char *s2)
{
	char	*rtrn;
	int		i;

	i = 0;
	if (!s2)
		return (0);
	rtrn = (char *)malloc(sizeof(char) * (ft_strlen_s(s1) + ft_strlen_s(s2)+1));
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
			exit(1); //revisar
		if (ref->def)
		{
			new_env[i] = ft_strjoin_s(new_env[i], ref->def);
			if (!new_env[i])
				exit(1); //revisar
		}
		ref = ref->next;
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}*/

/****************************************************************
						FINS AQUI
*****************************************************************/

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
	t_list *temp;

	temp = *env;
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
	*env = temp;
	if (!(*t_exec)->path)
		return (1); /*revisar com tractem l'error, aixi segur que no*/
	(*t_exec)->cmd = ft_strjoin("/", (*tokens)->wrd);
	if (!(*t_exec)->cmd)
		return (1); /*revisar com tractem l'error, aixi segur que no*/
	//*env = temp;
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
			exit (1); /*REVISAR COM FEM EXIT I QUIN VALOR */
		if (access((*t_exec)->absolute_path, X_OK) == 0)
			return (1);
		free((*t_exec)->absolute_path);
		i++;
	}
	/*hem de tractar si surt dek bucle, vol dir que no ha trobat*/
	//ft_error_cmd((*t_exec)->cmd_argv[0], 1); /*exemple de com fer-ho*/
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
		/*if (((*tokens)->tok == 3 || (*tokens)->tok == 4) && (*tokens)->next && (*tokens)->next->next)
		{		
			(*tokens) = (*tokens)->next;
			(*tokens) = (*tokens)->next;
		}//REVISANT*/
		t_exec->cmd_argv[i] = ft_strdup((*tokens)->wrd);
		if (!t_exec->cmd[i])
			return (1); /*revisar com tractem l'error, aixi segur que no*/
		*tokens = (*tokens)->next;
		i++;
	}
	/*t_exec->cmd_argv[i] = NULL;*/ //revisant
	i = 0;
//	while (t_exec->cmd_argv[i])
//		printf("EXEC_utils:%s\n", t_exec->cmd_argv[i++]);
	if (ft_exec_cmd(&t_exec))
		execve(t_exec->absolute_path, t_exec->cmd_argv, t_exec->new_envp);
	return (0);
}
