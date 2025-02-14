/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stdio.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:41:10 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/14 11:50:53 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_stdfds(t_io_fds *io, t_data *data);
void	restore_stdio(t_io_fds *io, t_data *data);
void	redirect_stdio(t_io_fds *io, t_data *data);

void	redirect_stdio(t_io_fds *io, t_data *data)
{
	if (!io)
		return ;
	init_stdfds(io, data);
	if (io->fd_in != -1)
	{
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
		{
			print_errno_str("redirect io.fd_in", NULL, strerror(errno));
			data->last_exit_code = errno;
		}
	}
	if (io->fd_out != -1)
	{
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		{
			print_errno_str("redirect io.fd_out", NULL, strerror(errno));
			data->last_exit_code = errno;
		}
	}
}
/*
duplicates the stdin and stdout to be restored later since dup2 will close it
*/
void	init_stdfds(t_io_fds *io, t_data *data)
{
	io->std_fds[STDIN_FILENO] = -1;
	io->std_fds[STDOUT_FILENO] = -1;
	io->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	if (io->std_fds[STDIN_FILENO] == -1)
	{
		print_errno_str("dup stdin", NULL, strerror(errno));
		data->last_exit_code = errno;
	}
	io->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	if (io->std_fds[STDOUT_FILENO] == -1)
	{
		print_errno_str("dup stdout", NULL, strerror(errno));
		data->last_exit_code = errno;
	}
}

void	restore_stdio(t_io_fds *io, t_data *data)
{
	if (!io)
		return ;
	if (io->std_fds[STDIN_FILENO] != -1)
	{
		if (dup2(io->std_fds[STDIN_FILENO], STDIN_FILENO) == -1)
			data->last_exit_code = errno;
		close(io->std_fds[STDIN_FILENO]);
		io->std_fds[STDIN_FILENO] = -1;
	}
	if (io->std_fds[STDOUT_FILENO] != -1)
	{
		if (dup2(io->std_fds[STDOUT_FILENO], STDOUT_FILENO) == -1)
			data->last_exit_code = errno;
		close(io->std_fds[STDOUT_FILENO]);
		io->std_fds[STDOUT_FILENO] = -1;
	}
}
