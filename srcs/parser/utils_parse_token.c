/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:45:06 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/07 15:25:58 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		validate_syntax(t_token **token);
void	detect_expandable_variable(t_token *token_node);
int		is_consecutive_operator(t_token *token_node);

int	validate_syntax(t_token **token)
{
	t_token	*temp;

	temp = *token;
	if (temp->type == PIPE)
	{
		print_syntax_error(PIPE_ERR_SYNTAX, NULL);
		return (FAILURE);
	}
	while (temp)
	{
		detect_expandable_variable(temp);
		if (is_consecutive_operator(temp))
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}

void	detect_expandable_variable(t_token *token_node)
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

int	is_consecutive_operator(t_token *token_node)
{
	int	is_true;

	is_true = 0;
	if (token_node->prev)
	{
		if ((token_node->type == PIPE && token_node->prev->type == PIPE) \
		|| (token_node->type > PIPE && token_node->prev->type > PIPE) \
		|| (token_node->type == EOF && token_node->prev->type >= PIPE))
			is_true = 1;
	}
	if (is_true)
	{
		if (token_node->type == END_OF_FILE && token_node->prev && token_node->prev->type > PIPE)
			print_syntax_error(NEWLINE_ERR_SYNTAX, NULL);
		else if (token_node->type == END_OF_FILE && token_node->prev)
			print_syntax_error(UNDEFINED, token_node->prev->value);
		else
			print_syntax_error(UNDEFINED, token_node->value);
		return (FAILURE);
	}
	return (SUCCESS);
}
