#include "../../include/minishell.h"

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

# define BUFFFER_SIZE 256
int	ft_pipes(t_token **tokens, t_list **env, t_list **export,  t_executor *t_exec)
{
	int	pipesfd[2];
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
			close(pipesfd[1]);
			ssize_t count = read(pipesfd[0], buffer, BUFFFER_SIZE - 1);
        	if (count == -1) {
            	perror("read");
            	exit(EXIT_FAILURE);
       		}
			buffer[count] = '\0';

        	// Imprimir el mensaje
        	printf("Recibido del comando: %s: ", (*tokens)->wrd);
			// un cop agafat el comando avancem fins a la seguent pipe, caldra mirar si existeix next i si s'han fet totes les pipes
			while ((*tokens)->tok != 2)
				(*tokens) = (*tokens)->next;
			(*tokens) = (*tokens)->next;
			printf("Mensaje: %s\n", buffer);
			(void)tokens;
			t_exec->cmd_count--;
			i++;
			wait(&status);
		}
	}
	return (0);	
}
