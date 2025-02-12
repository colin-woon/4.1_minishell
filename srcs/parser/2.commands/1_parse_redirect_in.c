/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse_redirect_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:28:10 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/12 19:38:09 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirect_in(t_cmd **last_cmd, t_token **tokens, t_data *data);
void	open_infile(t_io_fds *io, char *filename, t_data *data);

void	parse_redirect_in(t_cmd **last_cmd, t_token **tokens, t_data *data)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *tokens;
	cmd = get_last_cmd(*last_cmd);
	init_io_fds(cmd);
	open_infile(cmd->io_fds, temp->next->value, data);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*tokens = temp;
}

void	open_infile(t_io_fds *io, char *filename, t_data *data)
{
	if (io->infile)
	{
		if (io->fd_in == -1)
			return ;
		free_ptr((void **)&io->infile);
	}
	io->infile = ft_strdup(filename);
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
	{
		print_errno_str(io->infile, NULL, strerror(errno));
		data->last_exit_code = errno;
	}
}
