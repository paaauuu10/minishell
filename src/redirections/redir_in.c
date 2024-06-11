#include "../../include/minishell.h"

int	ft_redir_in(char *filename, t_executor *exec)
{
	int	fd;

	(void)exec;
	if (!filename)
		return (1);
	//if (!more_redirections(exp, '<') && exec->redirection[IN] == 0)
	//{
	fd = open (filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el archivo de entrada :(\n");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Error al redirigir :(\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
