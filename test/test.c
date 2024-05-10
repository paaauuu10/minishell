#include "../include/minishell.h"
#include <stdio.h>

int ft_fd_open(char **cmd)
{
    int fd;
    int i;
    int j;

    i = 0;
    while (ft_strnstr(cmd[i], ">", 1) == 0)
		i++;
    i++;
    j = i;
    fd = open(cmd[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
        //REVISAR
    }
    dup2(fd, STDOUT_FILENO);
    i = 0;
    while(cmd[i][0] != '>')
    {
        printf("%s ", cmd[i]);
        i++;   
    }
    close(fd);  
    return (0);
}
int ft_output_redirect(char **cmd)
{
    int i;
    //int flag;


    i = 0;
    while (cmd[i])
    {
        if (ft_strnstr(cmd[i], ">", 1) != 0)
            return (0);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    char **cmd;
    cmd = ft_split(argv[1], ' ');
    if (ft_output_redirect(cmd) == 0)
    {
        ft_fd_open(cmd);
        return (0);
    }
    argc = 0;
    printf("#########################\n");
    printf("#########################");
    return (1);
}