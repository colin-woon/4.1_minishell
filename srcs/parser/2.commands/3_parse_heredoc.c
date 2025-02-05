/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parse_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:05:49 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/05 20:44:55 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_heredoc(t_cmd **last_cmd, t_token **tokens);
void		run_heredoc(t_io_fds *io);
int			is_matching_heredoc_limiter(char *input, char *limiter);
static void	clean_up(char **input, char **temp);


void	parse_heredoc(t_cmd **last_cmd, t_token **tokens)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *tokens;
	cmd = get_last_cmd(*last_cmd);
	init_io_fds(cmd);
	cmd->io_fds->infile = HEREDOC_FILE;
	cmd->io_fds->heredoc_limiter = ft_strdup(temp->next->value);
	cmd->io_fds->fd_in = open(cmd->io_fds->infile, \
	O_WRONLY | O_APPEND | O_CREAT, 0644);
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
	char	*temp;

	temp = NULL;
	while (1)
	{
		set_signals_input();
		input = readline("> ");
		set_signals_execution();
		if (input == NULL)
			return (print_errno_str("warning", io->heredoc_limiter, \
			"here-document delimited by end-of-file"), \
			clean_up(&input, &temp));
		if (is_matching_heredoc_limiter(input, io->heredoc_limiter))
			break ;
		temp = ft_strjoin(input, "\n");
		write(io->fd_in, temp, ft_strlen(temp));
		clean_up(&input, &temp);
	}
	return (clean_up(&input, &temp));
}

int	is_matching_heredoc_limiter(char *input, char *limiter)
{
	if (!ft_strncmp(input, limiter, ft_strlen(limiter)) \
	&& ft_strlen(input) == ft_strlen(limiter))
		return (1);
	return (0);
}

static void	clean_up(char **input, char **temp)
{
		free_ptr((void **)input);
		free_ptr((void **)temp);
}
