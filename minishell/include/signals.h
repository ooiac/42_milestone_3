/* ************************************************************************** */
/*   signals.h - interface conceitual de sinais (comentado)                    */
/* ************************************************************************** */

#ifndef SIGNALS_H
#define SIGNALS_H

#include "minishell.h"

void	handle_sight(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals_prompt(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_prompt(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

#endif /* SIGNALS_H */
