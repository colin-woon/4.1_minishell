/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/07 18:55:32 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_data *data, char *input);
int	parse_tokens(t_token **token, t_data *data);
int	substitute_variable(t_data *data, t_token **token_list);
int	is_next_invalid(char next_token_char);
int	is_symbol_only_in_single_quotes(char *token_value, int i_current);

int	parse_input(t_data *data, char *input)
{
	if (tokenization(data, input) == FAILURE)
		return (FAILURE);
	if (parse_tokens(&data->tokens, data) == FAILURE)
		return (FAILURE);
	print_tokens(data->tokens);
	return (SUCCESS);
}

int	parse_tokens(t_token **token, t_data *data)
{
	if (validate_syntax(token) == FAILURE)
		return (FAILURE);
	substitute_variable(data, &data->tokens);
	return (SUCCESS);
}

int	substitute_variable(t_data *data, t_token **token_list)
{
	t_token	*temp;
	int		i;
	int		is_quote;

	temp = *token_list;
	while (temp)
	{
		is_quote = NO_QUOTE;
		if (temp->type == VARIABLE)
		{
			i = 0;
			while (temp->value[i])
			{
				is_quote = check_quote(is_quote, temp->value, i);
				if (temp->value[i] == '$' \
				&& !is_next_invalid(temp->value[i + 1]) \
				&& !is_symbol_only_in_single_quotes(temp->value, i) \
				&& (!is_quote || is_quote == DOUBLE_QUOTE))
					printf("substituting variable!\n");
					// replace_variable();
				i++;
			}
		}
		temp = temp->next;
	}
}

int	is_next_invalid(char next_token_char)
{
	if (next_token_char == '$' \
	|| next_token_char == ' ' \
	|| next_token_char == '=' \
	|| next_token_char == '\0')
		return (1);
	else
		return (0);
}

int	is_symbol_only_in_single_quotes(char *token_value, int i_current)
{
	if (i_current > 0)
	{
		if (token_value[i_current - 1] == '\'' \
		&& token_value[i_current + 1] == '\'')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
