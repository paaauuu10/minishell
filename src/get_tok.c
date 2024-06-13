/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:39:12 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/13 15:18:36 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	type_tok(char *s)
{
	if (s[0] == '>' && s[1] == '>' && s[2] == '\0')
		return (5);
	if (s[0] == '>' && s[1] == '\0')
		return (4);
	if (s[0] == '<' && s[1] == '\0')
		return (3);
	if (s[0] == '<' && s[1] == '<' && s[2] == '\0')
		return (6);
	if (s[0] == '|' && s[1] == '\0')
		return (2);
	if (ft_strcmp(s, "echo") || ft_strcmp(s, "cd") || ft_strcmp(s, "pwd")
		||ft_strcmp(s, "export") || ft_strcmp(s, "unset") || ft_strcmp(s, "env")
		|| ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

t_token	*new_token(char *s)
{
	t_token	*newtok;

	newtok = (t_token *)malloc(sizeof(t_token));
	if (!newtok)
		perror("newtok");
	newtok->wrd = ft_strdup(s);
	newtok->tok = type_tok(s);
	newtok->next = NULL;
	return (newtok);
}

t_token	**last_token(t_token **tokens)
{
	if (!tokens)
		return (NULL);
	while (*tokens)
	{
		if ((*tokens)->next == NULL)
			break;
		if ((*tokens)->next != NULL)
			tokens = &((*tokens)->next);
		else
			break;
	}
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


/*********************************************************
			LIBFT BOTA
**********************************************************/

int	ft_lstsize(t_token *lst)
{
	int		num;

	num = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		num++;
	}
	return (num);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*last;
	size_t	i;

	last = lst;
	i = ft_lstsize(lst);
	while (i > 1)
	{
		last = last->next;
		i--;
	}
	return (last);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}


/**********************************************************
			LIBFT BOTA
**********************************************************/

t_token	**get_tok(t_list **env, t_token **tokens, char *s)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = ft_quotes(s, env);
//	matrix = ft_split(s, ' ');
	if (!tokens)
		exit(2);
	while (matrix[i] && tokens)
		add_token(tokens, new_token(matrix[i++]));
/*	while (*tokens)
	{
		printf("%s\n",(*tokens)->wrd);
		if ((*tokens)->next)
			*tokens = (*tokens)->next;
		else
			break ;
	}*/
	return (tokens);
}
