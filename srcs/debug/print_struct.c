/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:48 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/21 14:38:30 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens);
void	print_envp_array(t_data *data);
void	print_value_str(char *message, char *value);
void	print_value_int(char *message, int value);
void	print_value_char(char *message, char value);

void	print_envp_array(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_array[i])
	{
		printf("%s\n", data->envp_array[i]);
		i++;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	while (current)
	{
		printf("Value: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	print_value_str(char *message, char *value)
{
	printf("%s %s\n", message, value);
}

void	print_value_int(char *message, int value)
{
	printf("%s %d\n", message, value);
}

void	print_value_char(char *message, char value)
{
	printf("%s %c\n", message, value);
}

void	print_io_fds(t_io_fds *io_fds)
{
	if (!io_fds)
	{
		printf("io_fds is NULL\n");
		return;
	}
	print_value_str("infile:", io_fds->infile ? io_fds->infile : "(null)");
	print_value_str("outfile:", io_fds->outfile ? io_fds->outfile : "(null)");
	print_value_str("heredoc_limiter:", io_fds->heredoc_limiter ? io_fds->heredoc_limiter : "(null)");
	print_value_int("is_heredoc_quotes:", io_fds->is_heredoc_quotes);
	print_value_int("fd_in:", io_fds->fd_in);
	print_value_int("fd_out:", io_fds->fd_out);
}

void	print_cmd(t_cmd *cmd)
{
	if (!cmd)
	{
		printf("cmd is NULL\n");
		return;
	}
	print_value_str("name:", cmd->name ? cmd->name : "(null)");
	print_value_str("path:", cmd->path ? cmd->path : "(null)");

	if (cmd->args)
	{
		int i = 0;
		printf("args:\n");
		while (cmd->args[i])
		{
			printf("  [%d]: %s\n", i, cmd->args[i]);
			i++;
		}
	}
	print_value_int("has_pipe:", cmd->has_pipe);

	if (cmd->pipe_fd)
	{
		printf("pipe_fd[0]: %d\n", cmd->pipe_fd[0]);
		printf("pipe_fd[1]: %d\n", cmd->pipe_fd[1]);
	}
	if (cmd->io_fds)
	{
		printf("io_fds:\n");
		print_io_fds(cmd->io_fds);
	}
}
