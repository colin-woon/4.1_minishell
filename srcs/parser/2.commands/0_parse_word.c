/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parse_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:38:15 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/06 14:36:38 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_word(t_cmd **cmd, t_token **tokens);
int		fill_cmd_args(t_token **current_tokens, t_cmd *last_cmd);
int		count_args_in_tokens(t_token *token);

void	parse_word(t_cmd **cmd, t_token **current_tokens)
{
	t_token	*temp;
	t_cmd	*last_cmd;

	temp = *current_tokens;
	while (temp->type == WORD || temp->type == VARIABLE)
	{
		last_cmd = get_last_cmd(*cmd);
		if (temp->prev == NULL || temp->prev->type == PIPE \
		|| last_cmd->name == NULL)
		{
			last_cmd->name = ft_strdup(temp->value);
			temp = temp->next;
		}
		else
			fill_cmd_args(&temp, last_cmd);
	}
	*current_tokens = temp;
}

int	fill_cmd_args(t_token **current_tokens, t_cmd *last_cmd)
{
	int		i;
	int		nb_of_args;
	t_token	*temp;

	temp = *current_tokens;
	nb_of_args = count_args_in_tokens(temp);
	last_cmd->args = malloc((nb_of_args + 2) * sizeof(char *));
	if (!last_cmd->args)
		return (FAILURE);
	i = 1;
	last_cmd->args[0] = ft_strdup(last_cmd->name);
	while (temp->type == WORD || temp->type == VARIABLE)
	{
		last_cmd->args[i] = ft_strdup(temp->value);
		i++;
		temp = temp->next;
	}
	last_cmd->args[i] = NULL;
	*current_tokens = temp;
	return (SUCCESS);
}

int	count_args_in_tokens(t_token *token)
{
	int		result;
	t_token	*temp;

	result = 0;
	temp = token;
	while (temp && (temp->type == WORD || temp->type == VARIABLE))
	{
		result++;
		temp = temp->next;
	}
	return (result);
}
