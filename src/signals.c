/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:52:19 by pborrull          #+#    #+#             */
/*   Updated: 2024/08/08 09:09:45 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	sig_handler(int sig);
//void	ctrl_c(int *exit_status);

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

void	signals(int	i)
{
	i = 0;
	struct sigaction	sa;
	//if (signal == 0)
	//	return ;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ctrlc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(56);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ctrls;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		exit(57);
	rl_catch_signals = 0;
	//signal = 0;
}


//inicializa variable global y las señales.
//Variable tc y sus funciones usan la libreria termios.h para no escribir ^C
/*void	signals(int i)
{
	struct termios	tc;

	ft_memset(&tc, 0, sizeof(struct termios));
	if (i == 1)
	{
		g_signal = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	if (i == 0)
		tc.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
}

void	ctrl_c(int *exit_status)
{
	if (g_signal == SIGINT)
		*exit_status = EXIT_FAILURE;
	signal(SIGINT, SIG_IGN);
}

//al recibir la señal SIGINT se ejecuta esta funcion,
//salta de linea y vuelve a mostrar el prompt
void	sig_handler(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}*/

