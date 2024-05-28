/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/28 13:20:52 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_count_pipes(t_executor *t_exec, t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	t_exec->total_pipes = 0;
	t_exec->d_pipe->flag = INACTIVE;
	while (temp)
	{
		if (ft_strcmp(temp->wrd, "|"))
		{
			t_exec->total_pipes++;
			t_exec->d_pipe->flag = ACTIVE;
		}
		temp = temp->next;
	}
	t_exec->d_pipe->pipecounter = t_exec->total_pipes;
}

int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (is_redirection(tokens))
		ft_redirect(tokens, env, export, t_exec);/*testejar*/
	else if (ft_is_builtin(tokens))
	{
		t_exec->exit_status = builtins(tokens, export, env);
		return (1); //revisar
	}
	else
	{
		t_exec->pid = fork();
		if (t_exec->pid < 0)
		{
			printf("pid < 0");
			return (0);   //revisar
		}
		if (t_exec->pid == 0)
		{
			ft_exec(tokens, env, t_exec); //s'ha de modificar
			//perror("Comand not found");
		}
	}
	ft_wait_one_child_process(&t_exec->exit_status); //aixo sha de revisar
	return (0); /*revisar*/
}
int	ft_save_fd(t_executor *t_exec)
{
	t_exec->d_pipe->original_stdin = dup(STDIN_FILENO);
	if (t_exec->d_pipe->original_stdin == -1)
	{
		perror("dup");
		return (1);
	}
	t_exec->d_pipe->original_stdout = dup(STDOUT_FILENO);
	if (t_exec->d_pipe->original_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	return (0);
}

void	ft_more_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int i;
	t_token *aux;
	t_token *temp;
	i = 0;
	temp = *tokens;
	t_exec->d_pipe->pipecounter = 0;
	while (*tokens)
	{
		if (t_exec->d_pipe->pipecounter != t_exec->total_pipes)
			pipe(t_exec->d_pipe->pipefd);
		t_exec->d_pipe->pipecounter++; /*aixi sabem quantes pipes portem creades i podem saber si es l'ultima*/
		//if (ft_is_redir_pipe(tokens)) //revisar redireccio fins que trobi la primera pipe
		//prerara la llista fins a pipe  /*creo llista o matriu*/ 
		aux = ft_lstnew(temp->wrd, temp->tok);
    	temp = temp->next;  
    	while (temp && ft_strcmp(temp->next->wrd, "|") == 1)
    	{
        	add_token(&aux, new_token(temp->wrd));
        	temp = temp->next;
   	 	}
		printf("PRIMERA PARAULA COMANDO ENVIAT: %s\n", aux->wrd);
		if (aux->next)
			printf("SEGONA PARAULA COMANDO ENVIAT: %s\n", aux->next->wrd);
		
		/************************************
	    ES POT REMPLAÇAR PER FT_CHILD_PROCESS
		*************************************/
		t_exec->pid = fork();
		if (t_exec->pid < 0)
		{
			perror ("pid"); /*revisar*/
			exit (1); /*revisar*/
		}
		if (t_exec->pid == 0) //fill
		{
			if (t_exec->d_pipe->pipecounter != t_exec->total_pipes) //si encara queda una pipe mes
				dup2(t_exec->d_pipe->pipefd[1], 1); //sortida del comando que s'executara a la std_out de la pipe
			if (!tokens || !*tokens)
				exit (0); /*revisar*/
			if (ft_is_builtin(&aux))
				exit(builtins(&aux, export, env));
			else
				exit(ft_exec(&aux, env, t_exec)); /*revisar si cal fer exit, ja que la funcion ja en te un (crec que si)*/
		}
		while ((*tokens)->next && (*tokens)->tok != PIPE) /*MIRO AVANÇAR FINS SEGUENT PIPE*/
				(*tokens) = (*tokens)->next;
		(*tokens) = (*tokens)->next;
		printf("comando despues de la pipe: %s\n", (*tokens)->wrd);
		//iterar fins el seguent comando
		if (t_exec->d_pipe->pipecounter != t_exec->total_pipes) //si encara hi ha pipe	
			dup2(t_exec->d_pipe->pipefd[0], 0);			
		if (t_exec->d_pipe->pipecounter == t_exec->total_pipes) //si es l'ulitm comando, no mes pipes
			dup2(t_exec->d_pipe->pipefd[0], t_exec->d_pipe->original_stdout);
		i++;
	}
	ft_wait_childs_process(&t_exec->exit_status, i, t_exec);
}


int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); /*revisar*/
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); /*revisar*/
	if (!tokens || !*tokens)
	{
		free(t_exec);
		return (0);
	}
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	if (t_exec->total_pipes == 0)
		ft_only_cmd(tokens, env, export, t_exec);
	else
		ft_more_cmd(tokens, env, export, t_exec);
	free(t_exec->d_pipe);
	free(t_exec);
	return (0);
}
