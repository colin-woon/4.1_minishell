/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:58:27 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/12 17:40:56 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		construct_commands(t_data *data, t_token *token);
static void	parse_one_word_command(t_data *data);

/*
- append_cmd in this case is just to initialize the cmd list

- since pipe is always the last part in a command,
parse pipe will set 1 for has_pipe in current command,
then append a new command and move on to the next token

- after parsing redirections-append-heredoc, AND IF there are sitll more tokens
then the token is iterated over the symbol and the filename/limiter for heredoc
otherwise it only iterates to the next token to so the loop condition can break

- parsing redirections-append have the same pattern and flow,
just use open() according to their required file permissions,
the IF statement to check infile and outfile to free
it is just to allow for consecutive redirections
eg: cat < file1 < file2

- parse one word command just duplicates the command name as args[0] for execve
 */
void	construct_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp->next != NULL)
	{
		if (temp == token)
			append_cmd(&data->cmd, create_cmd());
		if (temp->type == WORD || temp->type == VARIABLE)
			parse_word(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == REDIRECT_IN)
			parse_redirect_in(&data->cmd, &temp, data);
		else if (temp->type == REDIRECT_OUT)
			parse_redirect_out(&data->cmd, &temp, data);
		else if (temp->type == HEREDOC)
			parse_heredoc(&data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp, data);
		else if (temp->type == END_OF_FILE)
			break ;
	}
	parse_one_word_command(data);
}

/*
Duplicates the command name to the first element of the args 2d array
 */
static void	parse_one_word_command(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->name)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof(char *) * 2);
			cmd->args[0] = ft_strdup(cmd->name);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
}
