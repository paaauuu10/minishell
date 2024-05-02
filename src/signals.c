/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbotargu <pbotargu@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:52:19 by pborrull          #+#    #+#             */
/*   Updated: 2024/04/30 14:44:51 by pbotargu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrlc(int signal)
{
	signal = 0;
	ft_printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrls(int signal)
{
	signal = 0;
}

void	signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrlc;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(56);
	sa.sa_handler = ctrls;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		exit(57);
	rl_catch_signals = 0;
}
