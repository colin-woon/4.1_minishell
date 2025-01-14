/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/14 18:23:34 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_data *data, char *input);
int	parse_tokens(t_token **token, t_data *data);
void	handle_quotes(t_token **token_list);
void	remove_quotes(char *value, int is_quote_old, int *i);

int	parse_input(t_data *data, char *input)
{
	if (tokenization(data, input) == FAILURE)
		return (FAILURE);
	print_tokens(data->tokens);
	if (parse_tokens(&data->tokens, data) == FAILURE)
		return (FAILURE);
	printf("\n");
	print_tokens(data->tokens);
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

void	handle_quotes(t_token **token_list)
{
	t_token	*temp;
	int		is_quote;
	int		i;

	temp = *token_list;
	while (temp)
	{
		i = -1;
		is_quote = NO_QUOTE;
		while (temp->value[++i])
		{
			is_quote = check_quote(is_quote, temp->value, i);
			if (is_quote && (!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
				remove_quotes(temp->value, is_quote, &i);
			if (is_quote == SINGLE_QUOTE)
				remove_substring(temp->value, "'");
			else if (is_quote == DOUBLE_QUOTE)
				remove_substring(temp->value, "\"");
			if (temp->value[i] == '\0')
				break ;
		}
		temp = temp->next;
	}
}

void	remove_quotes(char *value, int is_quote_old, int *i)
{
	int	is_quote_new;

	++(*i);
	while (value[(*i)])
	{
		is_quote_new = NO_QUOTE;
		is_quote_new = check_quote(is_quote_new, value, (*i));
		if (is_quote_new == is_quote_old)
		{
			if (is_quote_new == SINGLE_QUOTE)
				remove_substring(value, "'");
			else if (is_quote_new == DOUBLE_QUOTE)
				remove_substring(value, "\"");
		}
		(*i)++;
	}
}
