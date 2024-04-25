/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:40:14 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/31 10:29:53 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_free(char	**str_free)
{
	if (*str_free)
	{
		free(*str_free);
		*str_free = NULL;
	}
	return (NULL);
}

char	*ft_next(char	*buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
		return (ft_free(&buf));
	line = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	if (!line)
		return (ft_free(&buf));
	i++;
	while (buf[i])
		line[j++] = buf[i++];
	ft_free(&buf);
	return (line);
}

char	*ft_line(char	*buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf || !buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_read_fd(int fd, char *buf)
{
	char	*buffer;
	int		num_byte;

	num_byte = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&buf));
	while (num_byte > 0)
	{
		num_byte = read(fd, buffer, BUFFER_SIZE);
		if (num_byte == -1)
		{
			ft_free(&buf);
			return (free(buffer), NULL);
		}
		buffer[num_byte] = 0;
		buf = ft_strjoin(buf, buffer);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buffer);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char		*buf = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!buf || (buf && !ft_strchr(buf, '\n')))
		buf = ft_read_fd(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_line(buf);
	if (!line)
		return (ft_free(&buf));
	buf = ft_next(buf);
	return (line);
}

/*int main(void)
{
    int fd;      char *line;

    fd = open("text.txt", O_RDONLY); 
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("res :%s", line);
		free(line);
	}
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	free(line);
    close(fd); 
    return (0);
}*/

/*
int	main(void)
{
	char	*t;
	t = get_next_line(2);
	printf("El text es: %s\n", t);
	return (0);
}*/
