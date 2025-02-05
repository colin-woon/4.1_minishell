/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:48 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/05 12:35:57 by cwoon            ###   ########.fr       */
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
void		signal_print_newline(int signal);
void		set_signals_execution(void);

/**
 * @file signals.c
 * Signal handling functions for the minishell program
 */
/**
 * @brief Sets up signal handlers for input mode
 *
 * Configures SIGINT (Ctrl+C) to display a new prompt
 * and ignores SIGQUIT (Ctrl+\)
 */
void	set_signals_input(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_sigint;
	sigaction(SIGINT, &act, NULL);
}

/**
 * @brief Ignores SIGQUIT signal
 *
 * Sets up signal handler to ignore SIGQUIT (Ctrl+\)
 * using SIG_IGN handler
 */
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/**
 * @brief Handles SIGINT (Ctrl+C) signal
 *
 * @param signum Signal number (unused)
 *
 * When SIGINT is received:
 * - Prints a newline
 * - Moves to a new line in readline
 * - Clears the current input line
 * - Redisplays the prompt
 */
static void	handle_sigint(int signum)
{
	(void)signum;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_execution(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_print_newline(int signal)
{
	if (signal == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	else if (signal == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
}
