/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_redirect_out.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:43:52 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/06 14:41:40 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_outfile_truncate(t_io_fds *io, char *filename, t_data *data);
void	parse_redirect_out(t_cmd **last_cmd, t_token **tokens, t_data *data);

void	parse_redirect_out(t_cmd **last_cmd, t_token **tokens, t_data *data)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *tokens;
	cmd = get_last_cmd(*last_cmd);
	init_io_fds(cmd);
	open_outfile_truncate(cmd->io_fds, temp->next->value, data);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*tokens = temp;
}

void	open_outfile_truncate(t_io_fds *io, char *filename, t_data *data)
{
	io->outfile = ft_strdup(filename);
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
	{
		print_errno_str(io->outfile, NULL, strerror(errno));
		data->last_exit_code = errno;
	}
}
