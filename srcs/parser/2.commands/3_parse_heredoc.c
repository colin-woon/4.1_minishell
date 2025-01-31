/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parse_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:05:49 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/31 18:05:49 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_heredoc(t_cmd **last_cmd, t_token **tokens);
void	run_heredoc(t_io_fds *io);
int		is_matching_heredoc_limiter(char *input, char *limiter);

void	parse_heredoc(t_cmd **last_cmd, t_token **tokens)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *tokens;
	cmd = get_last_cmd(*last_cmd);
	init_io_fds(cmd);
	cmd->io_fds->infile = HEREDOC_FILE;
	cmd->io_fds->heredoc_limiter = ft_strdup(temp->next->value);
	print_value_str("infile", cmd->io_fds->infile);
	print_value_str("LIMITER", cmd->io_fds->heredoc_limiter);
	cmd->io_fds->fd_in = open(cmd->io_fds->infile, O_WRONLY | O_CREAT, 0644);
	run_heredoc(cmd->io_fds);
	close(cmd->io_fds->fd_in);
	cmd->io_fds->fd_in = open(cmd->io_fds->infile, O_RDONLY);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*tokens = temp;
}

void	run_heredoc(t_io_fds *io)
{
	char	*input;
	char	*buffer;

	buffer = ft_strdup("");
	if (buffer == NULL)
		return ;
	while (1)
	{
		// set_signals();
		input = readline("> ");
		if (input == NULL)
			return (free_ptr(input), free_ptr(buffer));
		if (is_matching_heredoc_limiter(input, io->heredoc_limiter))
			break ;
		buffer = ft_strjoin(buffer, input);
		if (buffer == NULL)
			return (free_ptr(input), free_ptr(buffer));
		free_ptr(input);
	}
	write(io->fd_in, buffer, ft_strlen(buffer));
	return (free_ptr(buffer), free_ptr(input));
}

/*
Second if statement with the +1 includes the newline character
 */
int	is_matching_heredoc_limiter(char *input, char *limiter)
{
	print_value_str("input", input);
	print_value_str("limiter", limiter);
	if (!ft_strncmp(input, limiter, ft_strlen(limiter)))
	{
		// if (ft_strlen(input) == ft_strlen(limiter) + 1)
			return (1);
	}
	return (0);
}
