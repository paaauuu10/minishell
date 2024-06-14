/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:55:29 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/14 11:58:18 by pborrull         ###   ########.fr       */
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

/*---------------------------------------------------------------------------------*/
int	ft_only_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	if (ft_is_builtin(tokens))
	{
		builtins(tokens, export, env);
		return (1);
	}
	t_exec->pid = fork();
	if (t_exec->pid < 0)
	{
		printf("pid < 0");
		return (0);   //revisar
	}
	if (t_exec->pid == 0)
	{
		
		if (is_redirection(tokens))
		{
			ft_redirect(tokens, env, export, t_exec); //testejar
			exit (1); //revisar valor d'exit
		}
		//else if (ft_is_builtin(tokens))
		//{
		//	exit(builtins(tokens, export, env));
			//revisar
		//}
		else
		{
			ft_exec(tokens, env, t_exec); //s'ha de modificar
			exit(127);
		}
		exit(1); //revisar			//perror("Comand not found");
	}
	ft_wait_one_child_process(); //aixo sha de revisar
	return (0); //revisar
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
	(void)env;
	(void)export;
	int	prev_pipefd[2];
	t_exec->d_pipe->pipecounter = 0;
	while (*tokens)
	{
		pipe(t_exec->d_pipe->pipefd);
		t_exec->pid = fork();
		// controlar error pid;
		if (t_exec->pid == 0)
		{
			if (t_exec->d_pipe->pipecounter <= t_exec->total_pipes)
			{
				dup2(t_exec->d_pipe->pipefd[1], 1);
				close(t_exec->d_pipe->pipefd[0]);
				close(t_exec->d_pipe->pipefd[1]);
			}
			if (t_exec->d_pipe->pipecounter != t_exec->total_pipes)
			{
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
		//	ft_send_new_list(tokens, env, export, t_exec); //crear aquesta funcio
		//	ft_only_cmd(tokens, env, export, t_exec);
			exit(1); //revisar exit
		}
		else
		{
	//		ft_wait_one_child();
			if (t_exec->d_pipe->pipecounter <= t_exec->total_pipes)
				close(t_exec->d_pipe->pipefd[1]);
			if (t_exec->d_pipe->pipecounter != t_exec->total_pipes)
			{
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
			prev_pipefd[0] = t_exec->d_pipe->pipefd[0];
			prev_pipefd[1] = t_exec->d_pipe->pipefd[1];
			//ft_wait_one_child();	
			while (*tokens && ((*tokens)->tok != 2))
			{
				printf("Word: %s\n", (*tokens)->wrd);
				printf("Token: %d\n", (*tokens)->tok); // Imprimir el tipo de token para depuración
				(*tokens) = (*tokens)->next;
			}
			if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
		}
	}
}

/*void	ft_more_cmd(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
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
		t_exec->d_pipe->pipecounter++; //aixi sabem quantes pipes portem creades i podem saber si es l'ultima
		//if (ft_is_redir_pipe(tokens)) //revisar redireccio fins que trobi la primera pipe
		//prerara la llista fins a pipe  //creo llista o matriu 
		//aux = ft_lstnew(temp->wrd, temp->tok);
    	//temp = temp->next;  
    	//while (temp && ft_strcmp(temp->next->wrd, "|") == 1)
    	//{
        //	add_token(&aux, new_token(temp->wrd));
        //	temp = temp->next;
   	 //	}
	//	printf("PRIMERA PARAULA COMANDO ENVIAT: %s\n", aux->wrd);
	//	if (aux->next)
	//		printf("SEGONA PARAULA COMANDO ENVIAT: %s\n", aux->next->wrd);
		
	    				//ES POT REMPLAÇAR PER FT_CHILD_PROCESS
		t_exec->pid = fork();
		if (t_exec->pid < 0)
		{
			perror ("pid"); //revisar
			exit (1); //revisar
		}
		if (t_exec->pid == 0) //fill
		{
			printf("PROCES FILL\n");
			//if (t_exec->d_pipe->pipecounter != t_exec->total_pipes) //si encara queda una pipe mes
			dup2(t_exec->d_pipe->pipefd[1], 1); //sortida del comando que s'executara a la std_out de la pipe
			printf("Read end: %d\n", t_exec->d_pipe->pipefd[0]);
    			printf("Write end: %d\n", t_exec->d_pipe->pipefd[1]);
			if (!tokens || !*tokens)
				exit (0); //revisar
			if (ft_is_builtin(&aux))
			{
				printf("acaba FILL0\n");
				exit(builtins(&aux, export, env));
			}
			else
			{
				printf("acaba FILL1\n");
				exit(ft_exec(&aux, env, t_exec)); //revisar si cal fer exit, ja que la funcion ja en te un (crec que si)
			}
		}
		while ((*tokens)->tok != PIPE) //MIRO AVANÇAR FINS SEGUENT PIPE
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
}*/

/**********************************************************************
				TRYING NEW EXECUTOR
**********************************************************************/
int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); //revisar
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); //revisar
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

/*void	ft_exec_child(t_executor *t_exec, t_token **tokens, t_list **env, t_list **export)
{
	if (t_exec->pid == 0)
	{
		//TREBALLAR LES PIPES
		//CAL COMPROVAR TOKENS?
		if (ft_is_builtin(tokens))
			exit(builtins(tokens, env, export));
	}
}

int	ft_executor(t_token **tokens, t_list **env, t_list **export)
{
	t_executor	*t_exec;
	t_exec = malloc(sizeof(t_executor));
	if (!t_exec)
		exit(1); //revisar
	t_exec->d_pipe = malloc(sizeof(t_pipe));
	if (!t_exec->d_pipe)
		exit(1); //revisar
	if (!tokens || !*tokens)
	{
		free(t_exec->d_pipe);
		free(t_exec);
		return (0);
	}
	ft_count_pipes(t_exec, tokens);
	ft_save_fd(t_exec);
	t_exec->pid = fork();
	if (t_exec->pid < 0)
	{
		perror("FORK");
		exit(12);
	}
	ft_exec_child(t_exec, tokens, env, export);
	ft_wait_one_child_process();
	free(t_exec->d_pipe);
	free(t_exec);
	return (0);
}*/

