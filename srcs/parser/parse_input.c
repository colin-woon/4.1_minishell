/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/06 14:35:00 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_input(t_data *data, char *input);
int		parse_tokens(t_token **token, t_data *data);
int		is_input_spaces(char *input);

int	parse_input(t_data *data, char *input)
{
	if (input == NULL)
		exit_process(data, data->last_exit_code);
	else if (is_input_spaces(input))
		return (FAILURE);
	add_history(input);
	if (tokenization(data, input) == FAILURE)
	{
		data->last_exit_code = QUOTE_ERROR;
		return (FAILURE);
	}
	if (parse_tokens(&data->tokens, data) == FAILURE)
	{
		data->last_exit_code = SYNTAX_ERROR;
		return (FAILURE);
	}
	if (data->tokens->type != END_OF_FILE)
		construct_commands(data, data->tokens);
	return (SUCCESS);
}

int	parse_tokens(t_token **token, t_data *data)
{
	if (validate_syntax(token) == FAILURE)
		return (FAILURE);
	substitute_variable(data, &data->tokens);
	handle_quotes(&data->tokens);
	return (SUCCESS);
}

int	is_input_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}
