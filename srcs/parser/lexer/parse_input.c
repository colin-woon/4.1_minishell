/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/06 19:14:06 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_data *data, char *input);
int	parse_tokens(t_token **token);

int	parse_input(t_data *data, char *input)
{
	if (tokenization(data, input) == FAILURE)
		return (FAILURE);
	if (parse_tokens(&data->tokens) == FAILURE)
		return (FAILURE);
	// expand_variable(data, &data->tokens);
	// print_tokens(data->tokens);
	return (SUCCESS);
}

int	parse_tokens(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == PIPE)
	{
		print_syntax_error(PIPE_ERR_SYNTAX, NULL);
		return (FAILURE);
	}
	while (temp)
	{
		detect_expandable_variable(temp);
		if (is_consecutive_operator(temp))
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}

