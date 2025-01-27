/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:58:27 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/27 13:53:46 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		construct_commands(t_data *data, t_token *token);
static void	parse_one_word_command(t_data *data);

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
			parse_redirect_in(&data->cmd, &temp);
		else if (temp->type == REDIRECT_OUT)
			parse_redirect_out(&data->cmd, &temp);
		else if (temp->type == HEREDOC)
			parse_heredoc(&data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);
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
