/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:30 by pbotargu          #+#    #+#             */
/*   Updated: 2024/06/28 15:31:31 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *filename_2(t_token **tokens)
{
	t_token *aux;

	aux = *tokens;
	while (aux->tok != 3)
		aux = aux->next;
	aux = aux->next;
	if (aux->tok == 3)
		aux = aux->next;
	return (aux->wrd);
}

char *filename(t_token **tokens)
{
	t_token *aux;

	aux = *tokens;
	while (aux->tok != 4)
		aux = aux->next;
	aux = aux->next;
	if (aux->tok == 4)
		aux = aux->next;
	return (aux->wrd);	
}

void	ft_new_list_exec(t_token **tokens, t_token **aux)
{
	(*aux) = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->tok == 4)
		return ;
	while ((*tokens) && ft_strcmp((*tokens)->wrd, ">") == 0)
	{
		add_token(aux, new_token((*tokens)->wrd));
		(*tokens) = (*tokens)->next;
	}
}

int	ft_red_out(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int fd;
	t_token **aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	fd = 0;
	if (t_exec->redir_type == REDIR_IN)
		fd = open(filename_2(tokens), O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (1);
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdin, STDIN_FILENO);
	free(aux);
	return (0);
}

int	ft_red_in(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	int	fd;

	t_token **aux;

	aux = malloc(sizeof(t_token));
	*aux = NULL;
	fd = 0;
	if (t_exec->redir_type == REDIR_OUT_APPEND)
		fd = open(filename(tokens), O_CREAT | O_WRONLY | O_APPEND, 0660);
	else if (t_exec->redir_type == REDIR_OUT)
		fd = open(filename(tokens), O_CREAT | O_WRONLY | O_TRUNC, 0660);
	if (fd == -1)
		return (1);

	if (dup2(fd, STDOUT_FILENO) == -1)
		return (1);
	ft_new_list_exec(tokens, aux);
	ft_executor_2(aux, env, export, t_exec);
	close(fd);
	dup2(t_exec->d_pipe->original_stdout, STDOUT_FILENO);
	free(aux);
	return (0);
}

int	ft_red(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	ft_redirect(tokens, env, export, t_exec);
	if (t_exec->redir_type == REDIR_OUT || t_exec->redir_type == REDIR_OUT_APPEND)
		ft_red_in(tokens, env, export, t_exec);
	else if (t_exec->redir_type == REDIR_IN || t_exec->redir_type == HEREDOC)
		ft_red_out(tokens, env, export, t_exec);
	return (0);
}

int ft_redirs(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec)
{
	ft_red(tokens, env, export, t_exec);
	return (1);
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
i				exit (0); //revisar
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

/*int	ft_pipes(t_token **tokens, t_list **env, t_list **export,  t_executor *t_exec)
{
	int	pipesfd[2];
	int	prev_pipe[2] = {-1, -1};
	int status;
	char buffer[BUFFFER_SIZE];
	int i = 1;
	t_token *aux;
	
	while (t_exec->total_pipes != 0)
	{
		if (t_exec->total_pipes != 0)
		{
			pipe(pipesfd);
			t_exec->total_pipes--;
		}
		t_exec->pid = fork();
		if (t_exec->pid == 0)
		{
			if (prev_pipe[0] != -1) // vol dir que ja hi ha pipes previes
			{
				close(prev_pipe[1]); // Close write end of old pipe
                dup2(prev_pipe[0], STDIN_FILENO); // Redirect stdin to read end of old pipe
                close(prev_pipe[0]);

			}
			close(pipesfd[0]);
			dup2(pipesfd[1], STDOUT_FILENO);
			close (pipesfd[1]);
			//printf("HOLA\n");
			//crear nova llista
			aux = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
    		while ((*tokens) && ft_strcmp((*tokens)->next->wrd, "|") == 1)
    		{
        		add_token(&aux, new_token((*tokens)->wrd));
        		(*tokens) = (*tokens)->next;
   	 		}
			while (aux && aux->next)
			{
				printf("%s\n", aux->wrd);
				aux = aux->next;
			}
			ft_only_cmd(&aux, env, export, t_exec);
			exit(1);
		}
		else
		{
			if (prev_pipe[0] != -1)
			{
				close(prev_pipe[0]);
                close(prev_pipe[1]);
			}
			//update_info
			prev_pipe[0] = pipesfd[0];
            prev_pipe[1] = pipesfd[1];
			// un cop agafat el comando avancem fins a la seguent pipe, caldra mirar si existeix next i si s'han fet totes les pipes
			while ((*tokens)->tok != 2)
				(*tokens) = (*tokens)->next;
			(*tokens) = (*tokens)->next;
			t_exec->cmd_count--;
			i++;
			wait(&status);
		}
	}
	return (0);	
}*/

# define BUFFFER_SIZE 1024

/*int ft_pipes(t_token **tokens, t_list **env, t_list **export, t_executor *t_exec) {
    int prev_pipe[2] = {-1, -1}; // Inicializa prev_pipe correctamente
    int new_pipe[2];
    int status;
    t_token *aux;

    while (t_exec->total_pipes > 0) {
        if (pipe(new_pipe) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        t_exec->total_pipes--;

        t_exec->pid = fork();
        if (t_exec->pid == 0) { // Proceso hijo
            if (prev_pipe[0] != -1) { // Si hay una tubería anterior
                dup2(prev_pipe[0], STDIN_FILENO); // Redirige la entrada estándar
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }

            close(new_pipe[0]); // Cierra el extremo de lectura de la nueva tubería
            //if (t_exec->total_pipes > 0) { // Si no es el último comando
              //  dup2(new_pipe[1], STDOUT_FILENO); // Redirige la salida estándar
         //   }
            //close(new_pipe[1]);

            // Procesar el comando actual
            aux = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
            if ((*tokens)->next)
				(*tokens) = (*tokens)->next;
			while ((*tokens) && ft_strcmp((*tokens)->next->wrd, "|") != 0) {
                add_token(&aux, new_token((*tokens)->wrd));
                (*tokens) = (*tokens)->next;
            }
			while (aux && aux->next->wrd)
			{
					printf("Lista comando: %s\n", aux->wrd);
					aux = aux->next;
			}
			if (aux)
				printf("Lista comando: %s\n", aux->wrd);
            ft_only_cmd(&aux, env, export, t_exec); // Ejecuta el comando
            close(new_pipe[1]);
			exit(EXIT_FAILURE); // Si exec falla, salir con error
        } else { // Proceso padre
			char buffer[BUFFER_SIZE];
    		ssize_t bytes_read;
            if (prev_pipe[0] != -1) {
                close(prev_pipe[0]); // Cierra el extremo de lectura de la tubería anterior
                close(prev_pipe[1]); // Cierra el extremo de escritura de la tubería anterior
            }

            prev_pipe[0] = new_pipe[0];
            prev_pipe[1] = new_pipe[1];
			
			printf("Contenido de la tubería:\n");
        	while ((bytes_read = read(prev_pipe[0], buffer, BUFFFER_SIZE - 1)) > 0) {
            	buffer[bytes_read] = '\0'; // Asegurar la cadena terminada en NULL
            printf("%s", buffer); // Imprimir el contenido leído
        }
            // Avanzar el puntero de tokens hasta el próximo comando
            while ((*tokens)->tok != 2 && (*tokens)->next) {
                (*tokens) = (*tokens)->next;
            }
            if ((*tokens)->next) {
                (*tokens) = (*tokens)->next;
            }

            t_exec->cmd_count--;
            wait(&status);
        }
    }

    // Procesar el último comando
    t_exec->pid = fork();
    if (t_exec->pid == 0) { // Proceso hijo
        if (prev_pipe[0] != -1) { // Si hay una tubería anterior
            dup2(prev_pipe[0], STDIN_FILENO); // Redirige la entrada estándar
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }

        // Ejecuta el último comando
        aux = ft_lstnew((*tokens)->wrd, (*tokens)->tok);
        while ((*tokens)) {
            add_token(&aux, new_token((*tokens)->wrd));
            (*tokens) = (*tokens)->next;
        }

        ft_only_cmd(&aux, env, export, t_exec); // Ejecuta el comando
        exit(EXIT_FAILURE); // Si exec falla, salir con error
    } else { // Proceso padre
        if (prev_pipe[0] != -1) {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }

        wait(&status);
    }

    return 0;
}*/
