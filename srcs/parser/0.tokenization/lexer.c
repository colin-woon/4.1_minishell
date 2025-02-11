/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:59:17 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/11 18:35:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tokenization(t_data *data, char *input);
static int	save_word_or_seperator(int *i_current, \
		char *input, int from, t_data *data);
static void	save_word(int from, char *input, int i_current, t_token **tokens);
static void	save_seperator(int i_current, int type, \
		char *input, t_token **tokens);

/*
As long as no quotes, a word or seperator will be detected,
meaning if number of quotes are EVEN, the index will increment accordingly with
from & i_current

After saving word/seperator, from will increment accordingly,
i_current is also incremented in the function

!= NO_QUOTE handles unclosed quotes

QUOTES ARE SAVED TOGETHER AT THIS POINT
 */
int	tokenization(t_data *data, char *input)
{
	int	i_current;
	int	end;
	int	from;
	int	is_quote;

	i_current = -1;
	from = 0;
	end = ft_strlen(input);
	is_quote = NO_QUOTE;
	while (++i_current <= end)
	{
		is_quote = check_quote(is_quote, input, i_current);
		if (is_quote == NO_QUOTE)
			from = save_word_or_seperator(&i_current, input, from, data);
	}
	if (is_quote != NO_QUOTE)
	{
		if (is_quote == SINGLE_QUOTE)
			print_error(UNCLOSED_SINGLE_QUOTE);
		else if (is_quote == DOUBLE_QUOTE)
			print_error(UNCLOSED_DOUBLE_QUOTE);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
Includes the quotes when saving a word

- Detects seperator first, since this function relies on from and i_current:
--	NORMAL WORDS: seperator is the NULL terminator (-1 in our case),
	from is the first char b4 any seperator
	and i_current will be at the last char,
	so the function will keep exiting
	until it detects the NULL terminator as a seperator,
	then it saves both the word and the seperator as two different tokens

--	NORMAL SEPERATORS: the word and seperator is saved seperately
	eg: cat < Makefile

--	CONSECUTIVE WORDS AND SEPERATORS: same as NORMAL WORDS scenario
	eg: cat<Makefile

--	Dont have to worry about spaces between quotes as i_current will iterate
	over them due to the check_quote logic from the parent function

- For type > WORD, its referring to all seperators,
can refer to e_token_type in header file,

- from = (*i_current) + 1; , +1 helps to move on to the next char
	since the current one is processed
 */
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

/*
i_current - from + 1 = ft_strlen(word)
 */
static void	save_word(int from, char *input, int i_current, t_token **tokens)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (i_current - from + 1));
	if (!word)
		return (print_error(MALLOC_ERROR));
	while (from < i_current)
		word[i++] = input[from++];
	word[i] = '\0';
	append_token(tokens, create_token(word, WORD));
}

static void	save_seperator(int i_current, int type, \
	char *input, t_token **tokens)
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
	sep[i] = '\0';
	append_token(tokens, create_token(sep, type));
}
