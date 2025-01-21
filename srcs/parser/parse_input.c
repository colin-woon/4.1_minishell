/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/21 16:03:12 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_input(t_data *data, char *input);
int		parse_tokens(t_token **token, t_data *data);
void	construct_commands(t_data *data, t_token *token);

int	parse_input(t_data *data, char *input)
{
	if (tokenization(data, input) == FAILURE)
		return (FAILURE);
	// print_tokens(data->tokens);
	if (parse_tokens(&data->tokens, data) == FAILURE)
		return (FAILURE);
	if (data->tokens->type != END_OF_FILE)
		construct_commands(data, data->tokens);
	// printf("\n");
	// print_tokens(data->tokens);
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

void	construct_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	// while (temp->next != NULL)
	// {

	// }

}
