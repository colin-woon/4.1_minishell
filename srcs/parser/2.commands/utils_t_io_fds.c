/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_io_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:17 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/21 15:57:08 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io_fds	*create_io_fds(char *infile, char *outfile, char *heredoc_limiter, int is_heredoc_quotes);
void	free_io_fds(t_io_fds *io_fds);

t_io_fds	*create_io_fds(char *infile, char *outfile, char *heredoc_limiter, int is_heredoc_quotes)
{
	t_io_fds *new_io;

	new_io = (t_io_fds *)malloc(sizeof(t_io_fds));
	if (!new_io)
		return (NULL);
	new_io->infile = ft_strdup(infile);
	new_io->outfile = ft_strdup(outfile);
	new_io->heredoc_limiter = ft_strdup(heredoc_limiter);
	new_io->is_heredoc_quotes = is_heredoc_quotes;
	new_io->fd_in = -1;
	new_io->fd_out = -1;
	return (new_io);
}

void	free_io_fds(t_io_fds *io_fds)
{
	if (!io_fds)
		return;
	if (io_fds->infile)
		free_ptr(io_fds->infile);
	if (io_fds->outfile)
		free_ptr(io_fds->outfile);
	if (io_fds->heredoc_limiter)
		free_ptr(io_fds->heredoc_limiter);
	free_ptr(io_fds);
}

