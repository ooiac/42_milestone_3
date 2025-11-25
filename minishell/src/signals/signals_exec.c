/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fluca <fluca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:03:33 by fluca             #+#    #+#             */
/*   Updated: 2025/11/20 21:08:30 by fluca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

static  void    handle_sigint_exec(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    g_signal_received = SIGINT;
}

static  void    handle_sigquit_exec(int sig)
{
    (void)sig;
    write(1, "Quit (core dumped)\n", 19);
    g_signal_received = SIGQUIT;
}

void    setup_signals_exec(void)
{
    sa_int.sa_handler = handle_sigint_exec;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    sa_quit.sa_handler = handle_sigquit_exec;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
