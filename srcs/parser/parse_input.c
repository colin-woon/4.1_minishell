/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/11 18:33:06 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_input(t_data *data, char *input);
static int	parse_tokens(t_token **token, t_data *data);
static int	is_input_spaces(char *input);

/*
- handles ctrl D with exit builtin
- add_history is placed here to only record non-space inputs
- tokenization handles labeling, quotes will remain in tokens
- parse tokens will validate syntax, variable substitution and removes quotes
- construct commands uses the tokens to make a pseudo AST for execution
 */
int	parse_input(t_data *data, char *input)
{
	if (input == NULL)
		ft_exit(data, NULL);
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

static int	parse_tokens(t_token **token, t_data *data)
{
	if (validate_syntax(token) == FAILURE)
		return (FAILURE);
	substitute_variable(data, &data->tokens);
	handle_quotes(&data->tokens);
	return (SUCCESS);
}

static int	is_input_spaces(char *input)
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
