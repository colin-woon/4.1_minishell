/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:58:27 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/24 17:45:00 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	construct_commands(t_data *data, t_token *token);
void	parse_append(t_cmd **last_cmd, t_token **tokens);
void	open_outfile_append(t_io_fds *io, char *filename);


void	construct_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	// print_tokens(temp);
	while (temp->next != NULL)
	{
		// print_value_str("token is now", temp->value);
		if (temp == token)
			append_cmd(&data->cmd, create_cmd());
		if (temp->type == WORD || temp->type == VARIABLE)
			parse_word(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == REDIRECT_IN)
			parse_redirect_in(&data->cmd, &temp);
		else if (temp->type == REDIRECT_OUT)
			parse_redirect_out(&data->cmd, &temp);
		else if (temp->type == HEREDOC)
			parse_heredoc(&data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);
		else if (temp->type == END_OF_FILE)
			break ;
		// temp = temp->next;
	}
	// print_all_cmds(data->cmd);
}

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
	else
	{
		printf("append success!\n");
		close(io->fd_out);
	}
}
