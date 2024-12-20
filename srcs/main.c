/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/20 18:15:38 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_word_or_seperator(int *i_current, char *input, int from, t_data *data);
int	get_seperator(char *input, int i_current);
int	tokenization(t_data *data, char *input);
int	check_quote(int	is_quote, char *input, int i);

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	((void)ac, (void)av);
	ft_memset(&data, 0, sizeof(t_data));
	init_shell_data(&data, envp);
	while (1)
	{
		input = readline("minishell > ");
		add_history(input);
		tokenization(&data, input);
		// printf("%s\n", readline);
		free(input);
	}
}

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
			return (UNCLOSED_SINGLE_QUOTE);
		else if (is_quote == DOUBLE_QUOTE)
			return (UNCLOSED_DOUBLE_QUOTE);
		return (SYNTAX_ERROR);
	}
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

int	save_word_or_seperator(int *i_current, char *input, int from, t_data *data)
{
	int	type;

	type = get_seperator(input, (*i_current));
	printf("sepe is %d\n", type);
	// if (type)
	// {
	// 	if ((*i_current) != 0 && !get_separator(input, (*i_current) - 1))
	// 		save_word(from, input, (*i_current), &data->token);
	// }
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
