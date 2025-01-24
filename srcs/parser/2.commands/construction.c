/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:58:27 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/24 13:41:14 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	construct_commands(t_data *data, t_token *token);

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
		else if (temp->type == END_OF_FILE)
			break ;
		// temp = temp->next;
	}
	// print_all_cmds(data->cmd);
}

