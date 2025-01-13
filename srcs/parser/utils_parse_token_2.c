/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:01:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/11 15:07:52 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substitute_variable(t_data *data, t_token **token_list);
int	is_next_invalid(char next_token_char);
int	is_symbol_only_in_single_quotes(char *token_value, int i_current);
char	*get_variable(t_token *token, char *variable_name, t_data *data);

int	substitute_variable(t_data *data, t_token **token_list)
{
	t_token	*temp;
	int		i;
	int		is_quote;

	temp = *token_list;
	while (temp)
	{
		is_quote = NO_QUOTE;
		if (temp->type == VARIABLE)
		{
			i = 0;
			while (temp->value[i])
			{
				is_quote = check_quote(is_quote, temp->value, i);
				if (temp->value[i] == '$' \
				&& !is_next_invalid(temp->value[i + 1]) \
				&& !is_symbol_only_in_single_quotes(temp->value, i) \
				&& (!is_quote || is_quote == DOUBLE_QUOTE))
					printf("getting variable %s", get_variable(temp, temp->value + i + 1, data));
					// replace_variable();
				i++;
			}
		}
		temp = temp->next;
	}
}

int	is_next_invalid(char next_token_char)
{
	if (next_token_char == '$' \
	|| next_token_char == ' ' \
	|| next_token_char == '=' \
	|| next_token_char == '\0')
		return (1);
	else
		return (0);
}

int	is_symbol_only_in_single_quotes(char *token_value, int i_current)
{
	if (i_current > 0)
	{
		if (token_value[i_current - 1] == '\'' \
		&& token_value[i_current + 1] == '\'')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

char *get_variable(t_token *token, char *variable_name, t_data *data)
{
	int	variable_name_len;
	int	i_env;
	char	*extracted_var;
	char	*to_compare_var;

	i_env = 0;
	variable_name_len = 0;
	while (variable_name[variable_name_len])
	{
		if (is_next_invalid(variable_name[variable_name_len]))
			break;
		else
			variable_name_len++;
	}
	extracted_var = ft_substr(variable_name, 0, variable_name_len);
	to_compare_var = ft_strjoin(extracted_var, "=");
	printf("extracted %s\n", extracted_var);
	printf("to_compare_var %s\n", to_compare_var);
	while (data->envp_array[i_env])
	{
		if (!ft_strncmp(to_compare_var, data->envp_array[i_env], variable_name_len + 1))
		{
			printf("FOUND, GETTING VARIABLE\n");

		}
		// printf("this is %s\n", data->envp_array[i_env]);
		i_env++;
	}

	printf("result: %d\n", variable_name_len);
	return (variable_name);
}
