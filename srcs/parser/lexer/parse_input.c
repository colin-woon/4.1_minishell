/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/06 15:54:59 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(t_data *data, char *input);
int	parse_tokens(t_token **token);
void	detect_expandable_var(t_token *token_node);

int	parse_input(t_data *data, char *input)
{
	if (tokenization(data, input) == FAILURE)
		return (FAILURE);
	if (parse_tokens(&data->tokens) == FAILURE)
		return (FAILURE);
	print_tokens(data->tokens);
	return (SUCCESS);
}

int	parse_tokens(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == PIPE)
		return (FAILURE);
	while (temp)
	{
		detect_expandable_var(temp);
		// if (is_consecutive_operators(temp))
		// 	print_error(SYNTAX_ERROR);
		temp = temp->next;
	}
	return (SUCCESS);
}

void	detect_expandable_var(t_token *token_node)
{
	int	i;

	i = 0;
	while(token_node->value[i])
	{
		if (token_node->value[i] == '$')
			{
				if (token_node->prev && token_node->prev->type == HEREDOC)
					break;
				token_node->type = VARIABLE;
				return ;
			}
		i++;
	}
}
