/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_io_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:17 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/31 18:13:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_io_fds(t_cmd *cmd);
void	free_io_fds(t_io_fds *io_fds);

void	init_io_fds(t_cmd *cmd)
{
	if (cmd->io_fds)
		return ;
	cmd->io_fds = malloc(sizeof(t_io_fds));
	if (!cmd->io_fds)
	{
		g_last_exit_code = MALLOC_ERROR;
		return ;
	}
	cmd->io_fds->infile = NULL;
	cmd->io_fds->outfile = NULL;
	cmd->io_fds->heredoc_limiter = NULL;
	cmd->io_fds->is_heredoc_quotes = 0;
	cmd->io_fds->fd_in = -1;
	cmd->io_fds->fd_out = -1;
}

void	free_io_fds(t_io_fds *io_fds)
{
	if (!io_fds)
		return;
	if (!ft_strncmp(HEREDOC_FILE, io_fds->infile, ft_strlen(HEREDOC_FILE)))
		io_fds->infile = NULL;
	if (io_fds->infile)
		free_ptr(io_fds->infile);
	if (io_fds->outfile)
		free_ptr(io_fds->outfile);
	if (io_fds->heredoc_limiter)
		free_ptr(io_fds->heredoc_limiter);
	free_ptr(io_fds);
}

