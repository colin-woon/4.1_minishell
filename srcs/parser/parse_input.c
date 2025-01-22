/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:16:11 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/22 18:55:25 by cwoon            ###   ########.fr       */
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
void	parse_word(t_cmd **cmd, t_token **tokens);
int		fill_cmd_args(t_token **current_tokens, t_cmd *last_cmd);
int		count_args_in_tokens(t_token *token);
void	parse_pipe(t_cmd **cmd, t_token **current_tokens);

void	construct_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	// print_tokens(temp);
	while (temp->next != NULL)
	{
		print_value_str("token is now", temp->value);
		if (temp == token)
			append_cmd(&data->cmd, create_cmd());
		if (temp->type == WORD || temp->type == VARIABLE)
			parse_word(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == END_OF_FILE)
			break ;
		// temp = temp->next;
	}
	print_all_cmds(data->cmd);
}

void	parse_pipe(t_cmd **cmd, t_token **current_tokens)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd);
	last_cmd->has_pipe = 1;
	append_cmd(&last_cmd, create_cmd());
	*current_tokens = (*current_tokens)->next;
	printf("HELLO\n");
}

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
			// printf("hello\n");
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

	nb_of_args = count_args_in_tokens(temp);
	last_cmd->args = malloc((nb_of_args + 2) * sizeof(char *));
	if (!last_cmd->args)
	{
		g_last_exit_code = MALLOC_ERROR;
		return (FAILURE);
	}
	i = 1;
	temp = *current_tokens;
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
