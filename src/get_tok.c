/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:39:12 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/08 11:31:06 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	type_tok(char *s)
{
	if (s[0] == '>' && s[1] == '\0')
		return (4);
	if (s[0] == '<' && s[1] == '\0')
		return (3);
	if (s[0] == '|' && s[1] == '\0')
		return (2);
	if (ft_strcmp(s, "echo") || ft_strcmp(s, "cd") || ft_strcmp(s, "pwd")
		||ft_strcmp(s, "export") || ft_strcmp(s, "unset") || ft_strcmp(s, "env")
		|| ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

t_token	*new_token(char *s, int hd_nbr)
{
	t_token	*newtok;

	newtok = (t_token *)malloc(sizeof(t_token));
	if (!newtok)
		perror("newtok");
	newtok->wrd = ft_strdup(s);
	newtok->tok = type_tok(s);
	newtok->flag = 0;
	newtok->next = NULL;
	newtok->hd_nbr = hd_nbr;
	return (newtok);
}

t_token	**last_token(t_token **tokens)
{
	if (!tokens)
		return (NULL);
	while (*tokens && (*tokens)->next)
		tokens = &((*tokens)->next);
	return (tokens);
}

void	add_token(t_token **tokens, t_token	*node)
{
	t_token	**last;

	if (!node)
		return ;
	last = NULL;
	last = last_token(tokens);
	if (!last || !tokens || !node)
		return ;
	if (!(*tokens))
		*tokens = node;
	else
		(*last)->next = node;
}

t_token	**get_tok(t_list **env, t_token **tokens, char *s)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = ft_quotes(s, env);
	if (!tokens)
		exit(2);
	while (matrix[i] && tokens)
		add_token(tokens, new_token(matrix[i++], 0));
	i = 0;
	if (!matrix)
		exit(1);
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	matrix = NULL;
	return (tokens);
}
