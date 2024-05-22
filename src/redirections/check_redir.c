/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:49:46 by pbotargu          #+#    #+#             */
/*   Updated: 2024/05/22 10:41:34 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     is_redirection(t_token **tokens)
{
    t_token *temp;

    temp = *tokens;
    while(temp)
    {
        if (ft_strcmp(temp->wrd, ">") || \
        ft_strcmp(temp->wrd, "<") || \
        ft_strcmp(temp->wrd, ">>") || \
        ft_strcmp(temp->wrd, "<<"))
            return (1);
        temp = temp->next;
    }
    return (0);
}

/**
 * is_rd - Checks if a character is a redirection symbol.
 * c: The character to check.
 *
 * This function returns 1 if the character is a redirection symbol ('<' or '>').
 * Returns 0 if the character is not a redirection symbol.
 */
int	is_rd(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}
/**
 * check_rd - Checks the validity of a redirection character in a string.
 * str: The input string.
 * i: The position of the character to check.
 *
 * This function returns 1 if the redirection character at position i is invalid.
 * A character is considered invalid if it is at the start or end of the string,
 * or if it follows another redirection character ('<' or '>').
 * Returns 0 if the character is valid.
 */

int	check_rd(char *str, int i)
{
	if (i <= 0)
		return (1);
	if (!str[i + 1])
		return (1);
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}
/**
 * ft_is_redirection - Determines if a sequence of characters represents a valid redirection.
 * str: The input string.
 * i: The position of the character to check.
 *
 * This function returns 1 if the character at position i is part of a valid redirection sequence.
 * A valid redirection can be ">>", "<<<", or it cannot follow another redirection sequence of the same type.
 * Returns 0 if the sequence is not a valid redirection.
 */

int	ft_is_redirection(char *str, int i)
{
	if (i < 2)
		return (0);
	if (!str[i + 1])
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		return (1);
	if (i >= 2 && is_rd(str[i - 1]) && is_rd(str[i - 2]) && is_rd(str[i])) /*falta is_rd*/
		return (1);
	if (str[i] == '<' && str[i - 1] == '>')
		return (1);
	return (0);
}