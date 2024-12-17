/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/17 17:52:06 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenization(t_data *data);
void	get_strings(char ***strings, char *readline);
void	initialize_tokens(t_data *data);

int main()
{
	t_data data;

	while (1)
	{
		data.readline = readline("minishell > ");
		add_history(data.readline);
		tokenization(&data);
		// printf("%s\n", readline);
		free(data.readline);
	}
}

void	tokenization(t_data *data)
{
	int	count;

	get_strings(&data->strings, data->readline);
	count = 0;
	while (data->strings[count] != NULL)
		count++;
	data->total_tokens = count;
	initialize_tokens(data);
	printf("%d\n", data->total_tokens);
}

void	get_strings(char ***strings, char *readline)
{
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (readline[i])
	{
		if (readline[i] == SPACE && !in_quote)
			readline[i] = TO_SPLIT;
		else if ((readline[i] == '\'' || readline[i] == '"') && !in_quote)
			in_quote = 1;
		else if ((readline[i] == '\'' || readline[i] == '"') && in_quote)
			in_quote = 0;
		i++;
	}
	*strings = ft_split(readline, TO_SPLIT);

	i = 0;
	while ((*strings)[i] != NULL)
	{
		printf("Token %d: %s\n", i, (*strings)[i]);
		i++;
	}
}

void initialize_tokens(t_data *data)
{
	int	i;

	i = 0;
	data->tokens = malloc(data->total_tokens * sizeof(t_token));
	// if (data.tokens = NULL)
	// 	return(handle_error(data));
	while (data->strings[i] != NULL)
	{
		data->tokens[i].value = ft_strdup((const char *)data->strings[i]);
		printf("Token %d: %s\n", i, data->tokens[i].value);
		i++;
	}
}
