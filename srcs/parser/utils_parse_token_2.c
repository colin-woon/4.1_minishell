/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:01:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/13 16:59:16 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substitute_variable(t_data *data, t_token **token_list);
int	is_next_invalid(char next_token_char);
int	is_symbol_only_in_single_quotes(char *token_value, int i_current);
char	*get_variable(t_token *token, char *var_str, t_data *data);
char	*process_var_str(char *var_str, int *var_name_len);

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
				{
					printf("getting variable %s\n", get_variable(temp, temp->value + i + 1, data));
					// printf("NOTHING\n");
					// free(get_variable(temp, temp->value + i + 1, data));
				}
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

char *get_variable(t_token *token, char *var_str, t_data *data)
{
	int		var_name_len;
	int		i_env;
	char	*var_w_equal_sign;
	char	*real_var_value;

	i_env = -1;
	var_w_equal_sign = process_var_str(var_str, &var_name_len);
	real_var_value = NULL;
	while (data->envp_array[++i_env])
	{
		if (!ft_strncmp(var_w_equal_sign, \
		data->envp_array[i_env], var_name_len + 1))
		{
			real_var_value = ft_strdup(data->envp_array[i_env] + \
			var_name_len + 1);
			free_ptr(var_w_equal_sign);
			return (real_var_value);
		}
	}
	if (var_w_equal_sign[0] == '?')
		return (free_ptr(var_w_equal_sign), ft_itoa(g_last_exit_code));
	else
		return (free_ptr(var_w_equal_sign), NULL);
}

char	*process_var_str(char *var_str, int *var_name_len)
{
	char	*extract_var;
	char	*result;

	(*var_name_len) = -1;
	while (var_str[++(*var_name_len)])
	{
		if (is_next_invalid(var_str[(*var_name_len)]))
			break;
	}
	extract_var = ft_substr(var_str, 0, (size_t)(*var_name_len));
	result = ft_strjoin(extract_var, "=");
	free_ptr(extract_var);
	return(result);
}
