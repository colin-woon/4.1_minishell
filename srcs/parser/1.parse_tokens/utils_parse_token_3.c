/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:33:26 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/02 17:23:30 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(t_token **token_list);
void	remove_all_quotes(char *value, int is_quote_old, int *i);

/*
Removes quotes according to these conditions:
All same type of quotes							- remove all quotes
Internal quotes different from external quotes	- remove external quote only
Example:	"hello 'fake' world" > hello 'fake' world
			'hello "fake" world' > hello "fake" world
 */
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
			if (is_quote && \
			(!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
				remove_all_quotes(temp->value, is_quote, &i);
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

void	remove_all_quotes(char *value, int is_quote_old, int *i)
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
		if ((value[(*i)] == '\'' && is_quote_old == SINGLE_QUOTE) \
		|| (value[(*i)] == '"' && is_quote_old == DOUBLE_QUOTE))
			continue ;
		(*i)++;
	}
}
