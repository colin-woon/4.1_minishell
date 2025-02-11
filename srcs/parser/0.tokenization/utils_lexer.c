/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:17:46 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/11 15:51:08 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_seperator(char *input, int i_current);
int	check_quote(int is_quote, char *input, int i_current);

int	check_quote(int is_quote, char *input, int i_current)
{
	if (input[i_current] == '\'' && is_quote == NO_QUOTE)
		is_quote = SINGLE_QUOTE;
	else if (input[i_current] == '\'' && is_quote == SINGLE_QUOTE)
		is_quote = NO_QUOTE;
	else if (input[i_current] == '\"' && is_quote == NO_QUOTE)
		is_quote = DOUBLE_QUOTE;
	else if (input[i_current] == '\"' && is_quote == DOUBLE_QUOTE)
		is_quote = NO_QUOTE;
	return (is_quote);
}
/*
ELIF Order matters for << and >>
 */
int	get_seperator(char *input, int i_current)
{
	if (ft_isspace(input[i_current]))
		return (SPACES);
	else if (input[i_current] == '|')
		return (PIPE);
	else if (input[i_current] == '<' && input[i_current + 1] == '<')
		return (HEREDOC);
	else if (input[i_current] == '<')
		return (REDIRECT_IN);
	else if (input[i_current] == '>' && input[i_current + 1] == '>')
		return (APPEND);
	else if (input[i_current] == '>')
		return (REDIRECT_OUT);
	else if (input[i_current] == '\0')
		return (END_OF_FILE);
	else
		return (NONE);
}
