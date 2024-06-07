/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:52:19 by pborrull          #+#    #+#             */
/*   Updated: 2024/06/07 11:51:09 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrls(int signal)
{
	(void)signal;
}

void	signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrlc;
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(56);
	sa.sa_handler = ctrls;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		exit(57);
	rl_catch_signals = 0;
}
