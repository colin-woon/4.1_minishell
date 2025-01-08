/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:01:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/08 13:03:54 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substitute_variable(t_data *data, t_token **token_list);
int	is_next_invalid(char next_token_char);
int	is_symbol_only_in_single_quotes(char *token_value, int i_current);

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
