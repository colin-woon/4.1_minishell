/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parse_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:05:49 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/09 15:07:40 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_heredoc(t_cmd **last_cmd, t_token **tokens);
void		run_heredoc(t_io_fds *io);
int			is_matching_heredoc_limiter(char *input, char *limiter);
static void	clean_up(char **input, char **temp);
static void	handle_heredoc_sigint(int sig);

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
	g_is_heredoc_sigint = 0;
	set_signals_input();
	signal(SIGINT, handle_heredoc_sigint);
	while (1)
	{
		if (g_is_heredoc_sigint)
			return (unlink(io->infile), clean_up(&input, &temp));
		input = readline("> ");
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
	set_signals_execution();
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

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	g_is_heredoc_sigint = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
