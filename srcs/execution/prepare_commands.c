/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:18:29 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/06 14:35:00 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_data *data);
int	is_valid_files(t_io_fds *io);
int	prepare_commands(t_data *data);

int	prepare_commands(t_data *data)
{
	if (!data || !data->cmd)
		return (1);
	if (!data->cmd->name)
	{
		if (data->cmd->io_fds && !is_valid_files(data->cmd->io_fds))
		{
			data->last_exit_code = FAILURE;
			return (1);
		}
		return (1);
	}
	if (create_pipes(data) == FAILURE)
		return (1);
	return (CMD_NOT_FOUND);
}

int	is_valid_files(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}

int	create_pipes(t_data *data)
{
	t_cmd	*temp;

	temp = data->cmd;
	while (temp)
	{
		if (temp->has_pipe || (temp->prev && temp->prev->has_pipe))
		{
			if (pipe(temp->pipe_fd) != 0)
			{
				print_errno_str("create_pipes", NULL, strerror(errno));
				data->last_exit_code = FAILURE;
				garbage_collector(data, NULL, false);
				return (FAILURE);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
