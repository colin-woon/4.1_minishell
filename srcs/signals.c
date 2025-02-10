/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:48 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/10 22:58:06 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
SIGINT	(ctrl + c)
SIGQUIT	(ctrl + \)
EOF		(ctrl + d)
 */

void		ignore_sigquit(void);
static void	handle_sigint(int signum);
void		set_signals_input(void);
void		handle_execution_signals(int signal);
void		set_signals_execution(void);

/*
SIGINT	(ctrl + c) -- should go to newline
SIGQUIT	(ctrl + \) -- does nothing
 */
void	set_signals_input(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_sigint;
	sigaction(SIGINT, &act, NULL);
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

static void	handle_sigint(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
SIGINT	(ctrl + c) -- interrupts process
SIGQUIT	(ctrl + \) -- interrupts process with core dumped
(supposed to actually create a core dump file for logging
but thats too many steps)
 */
void	set_signals_execution(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = handle_execution_signals;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	handle_execution_signals(int signum)
{
	if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	else if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
}
