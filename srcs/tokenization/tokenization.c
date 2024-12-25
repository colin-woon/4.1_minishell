/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:59:17 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/25 19:07:36 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_word_or_seperator(int *i_current, char *input, int from, t_data *data);
int	get_seperator(char *input, int i_current);
int	tokenization(t_data *data, char *input);
int	check_quote(int	is_quote, char *input, int i);
void	save_word(int from, char *input, int i_current, t_token **tokens);
void	save_seperator(int i_current, int type, char *input, t_token **tokens);

int	tokenization(t_data *data, char *input)
{
	int	i_current;
	int	end;
	int	from;
	int	is_quote;

	i_current = 0;
	from = 0;
	end = ft_strlen(input);
	is_quote = NO_QUOTE;
	while(i_current <= end)
	{
		is_quote = check_quote(is_quote, input, i_current);
		if (is_quote == NO_QUOTE)
			from = save_word_or_seperator(&i_current, input, from, data);
		i_current++;
	}
	if (is_quote != NO_QUOTE)
	{
		if (is_quote == SINGLE_QUOTE)
			print_error(UNCLOSED_SINGLE_QUOTE);
		else if (is_quote == DOUBLE_QUOTE)
			print_error(UNCLOSED_DOUBLE_QUOTE);
		print_error(SYNTAX_ERROR);
	}
	print_tokens(data->tokens);
	return (SUCCESS);
}

int	check_quote(int	is_quote, char *input, int i_current)
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

// includes the quotes when saving a word
// for type > WORD, its referring to all seperators, can refer to e_token_type
// in header file,
int	save_word_or_seperator(int *i_current, char *input, int from, t_data *data)
{
	int	type;

	type = get_seperator(input, (*i_current));
	if (type)
	{
		if ((*i_current) != 0 && !get_seperator(input, (*i_current) - 1))
			save_word(from, input, (*i_current), &data->tokens);
		if (type > WORD || type == END_OF_FILE)
		{
			save_seperator((*i_current), type, input, &data->tokens);
			if (type == APPEND || type == HEREDOC)
				(*i_current)++;
		}
		from = (*i_current) + 1;
	}
	return (from);
}

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

void	save_word(int from, char *input, int i_current, t_token **tokens)
{
	int		i;
	char 	*word;

	i = 0;
	word = malloc(sizeof(char) * (i_current - from + 1));
	if (!word)
		return (print_error(MALLOC_ERROR));
	while (from < i_current)
		word[i++] = input[from++];
	word[i] = '\0';
	append_token(tokens, create_token(word, WORD));
}

void	save_seperator(int i_current, int type, char *input, t_token **tokens)
{
	int		i;
	char	*sep;
	int		sep_length;

	i = 0;
	if (type == APPEND || type == HEREDOC)
		sep_length = 2;
	else
		sep_length = 1;
	sep = malloc(sizeof(char) * (sep_length + 1));
	if (!sep)
		return (print_error(MALLOC_ERROR));
	while (i < sep_length)
		sep[i++] = input[i_current++];
	sep[i] == '\0';
	append_token(tokens, create_token(sep, type));
}
