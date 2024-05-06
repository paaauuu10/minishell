#include "../include/minishell.h"
#include "../include/libft/libft.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*tab;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
// 	if (tab == 0)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		tab[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		tab[i] = s2[j];
// 		j++;
// 		i++;
// 	}
// 	tab[i] = '\0';
// 	return (tab);
// }

// char	*ft_strnstr(const char *d, const char *s, size_t n)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (*s == '\0' || s == d)
// 		return ((char *)d);
// 	i = 0;
// 	while (d[i] && i < n)
// 	{
// 		j = 0;
// 		while (s[j] != '\0' && d[i + j] != '\0'
// 			&& d[i + j] == s[j] && (j + i) < n)
// 			j++;
// 		if (s[j] == '\0')
// 			return ((char *)d + i);
// 		i++;
// 	}
// 	return (0);
// }
// unsigned long	ft_len(char const *s, char c)
// {
// 	unsigned long	i;

// 	i = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			i++;
// 			while (*s && *s != c)
// 				s++;
// 		}
// 		else
// 			s++;
// 	}
// 	return (i);
// }

// char	**ft_aux2(char **r, char c, char const *s)
// {
// 	size_t	j;
// 	size_t	len;

// 	j = 0;
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			len = 0;
// 			while (*s && *s != c && ++len)
// 				s++;
// 			r[j] = ft_substr(s - len, 0, len);
// 			if (!r[j])
// 			{
// 				while (j-- > 0)
// 					free(r[j]);
// 				return (NULL);
// 			}
// 			j++;
// 		}
// 		else
// 			s++;
// 	}
// 	r[j] = 0;
// 	return (r);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**r;

// 	if (!s)
// 		return (NULL);
// 	r = malloc(sizeof (char *) * (ft_len(s, c) + 1));
// 	if (!r)
// 		return (NULL);
// 	if (!ft_aux2(r, c, s))
// 	{
// 		free(r);
// 		return (NULL);
// 	}
// 	return (r);
// }

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
int    ft_execute(char *argv, char **envp)
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
int main(int argc, char **argv, char **envp)
{
    ft_execute(argv[1], envp);
    return (0);
}