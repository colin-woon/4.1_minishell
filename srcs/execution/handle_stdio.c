/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stdio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:41:10 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/27 16:41:52 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_stdfds(t_io_fds *io);
void	restore_stdio(t_io_fds *io);
void	redirect_stdio(t_io_fds *io);

void	redirect_stdio(t_io_fds *io)
{
	if (!io)
		return ;
	init_stdfds(io);
	if (io->fd_in != -1)
	{
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
		{
			print_errno_str("redirect io.fd_in", strerror(errno));
			g_last_exit_code = errno;
		}
	}
	if (io->fd_out != -1)
	{
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		{
			print_errno_str("redirect io.fd_out", strerror(errno));
			g_last_exit_code = errno;
		}
	}
}


void	init_stdfds(t_io_fds *io)
{
	io->std_fds[STDIN_FILENO] = -1;
	io->std_fds[STDOUT_FILENO] = -1;
	io->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	if (io->std_fds[STDIN_FILENO] == -1)
	{
		print_errno_str("dup stdin", strerror(errno));
		g_last_exit_code = errno;
	}
	io->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (io->std_fds[STDOUT_FILENO] == -1)
	{
		print_errno_str("dup stdout", strerror(errno));
		g_last_exit_code = errno;
	}
}

void	restore_stdio(t_io_fds *io)
{
	if (!io)
		return ;
	if (io->std_fds[STDIN_FILENO] != -1)
	{
		if (dup2(io->std_fds[STDIN_FILENO], STDIN_FILENO) == -1)
		{
			print_errno_str("restore io.std_fds[stdin]", strerror(errno));
			g_last_exit_code = errno;
		}
		close(io->std_fds[STDIN_FILENO]);
		io->std_fds[STDIN_FILENO] = -1;
	}
	if (io->std_fds[STDOUT_FILENO] != -1)
	{
		if (dup2(io->std_fds[STDOUT_FILENO], STDOUT_FILENO) == -1)
		{
			print_errno_str("restore io.std_fds[stdout]", strerror(errno));
			g_last_exit_code = errno;
		}
		close(io->std_fds[STDOUT_FILENO]);
		io->std_fds[STDOUT_FILENO] = -1;
	}
}
