/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parse_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:46:26 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/24 17:48:33 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_append(t_cmd **last_cmd, t_token **tokens);
void	open_outfile_append(t_io_fds *io, char *filename);

void	parse_append(t_cmd **last_cmd, t_token **tokens)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *tokens;
	cmd = get_last_cmd(*last_cmd);
	init_io_fds(cmd);
	open_outfile_append(cmd->io_fds, temp->next->value);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*tokens = temp;
}

void	open_outfile_append(t_io_fds *io, char *filename)
{
	io->outfile = ft_strdup(filename);
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
	{
		print_errno_str(io->outfile, strerror(errno));
		g_last_exit_code = errno;
	}
}
