/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:01:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/14 17:55:44 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		substitute_variable(t_data *data, t_token **token_list);
char		*get_variable(t_token *token, char *var_str, t_data *data);
void		replace_variable(t_token *token_node, char *variable_name, \
char *variable_result);
static void	clean_up(char *extracted_var, char *var_w_equal_sign);
int			is_valid_variable(char *value, int i, int is_quote);

void	substitute_variable(t_data *data, t_token **token_list)
{
	t_token	*temp;
	int		i;
	int		is_quote;
	int		i_var;

	temp = *token_list;
	while (temp)
	{
		i_var = 1;
		is_quote = NO_QUOTE;
		if (temp->type == VARIABLE)
		{
			i = 0;
			while (temp->value[i])
			{
				is_quote = check_quote(is_quote, temp->value, i);
				if (is_valid_variable(temp->value, i, is_quote))
					replace_variable(temp, extract_var_without_symbol\
	(temp->value + i, &i_var), get_variable(temp, temp->value + i + 1, data));
				else
					i++;
			}
		}
		temp = temp->next;
	}
}

int	is_valid_variable(char *value, int i, int is_quote)
{
	if (value[i] == '$'
		&& !is_next_invalid(value[i + 1])
		&& !is_symbol_only_in_single_quotes(value, i)
		&& (!is_quote || is_quote == DOUBLE_QUOTE))
		return (1);
	return (0);
}

void	replace_variable(t_token *token_node, char *variable_name, \
char *variable_result)
{
	if (variable_result)
		token_node->value = replace_substring(token_node->value, \
			variable_name, variable_result);
	else
		remove_substring(token_node->value, variable_name);
	free_ptr(variable_name);
	free_ptr(variable_result);
}


static void	clean_up(char *extracted_var, char *var_w_equal_sign)
{
	free_ptr(extracted_var);
	free_ptr(var_w_equal_sign);
}

char	*get_variable(t_token *token, char *var_str, t_data *data)
{
	int		var_name_len;
	int		i_env;
	char	*extracted_var;
	char	*var_w_equal_sign;

	i_env = -1;
	var_name_len = 0;
	extracted_var = extract_var_without_symbol(var_str, &var_name_len);
	var_w_equal_sign = ft_strjoin(extracted_var, "=");
	while (data->envp_array[++i_env])
	{
		if (!ft_strncmp(var_w_equal_sign, \
		data->envp_array[i_env], var_name_len + 1))
		{
			return (clean_up(extracted_var, var_w_equal_sign), \
			ft_strdup(data->envp_array[i_env] + var_name_len + 1));
		}
	}
	free_ptr(extracted_var);
	if (var_w_equal_sign[0] == '?')
		return (free_ptr(var_w_equal_sign), ft_itoa(g_last_exit_code));
	else
		return (free_ptr(var_w_equal_sign), NULL);
}
