/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:01:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/05 13:12:53 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		substitute_variable(t_data *data, t_token **token_list);
char		*get_variable(char *var_str, t_data *data);
void		replace_variable(t_token *token_node, char *variable_name, \
char *variable_result);
int			is_valid_variable(char *value, int i, int is_quote);

/*
Only $VARIABLES in DOUBLE quotes will get substituted (includes if $ is empty)
IF only $ symbol in SINGLE quotes, it will not be substituted,
as per subject requirement,
the checking process is in FUNCTION - is_valid_variable

Edge Case: $? -- returns last exit code, handled in FUNCTION - get_variable
 */
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
					replace_variable(temp, extract_var_without_symbol \
	(temp->value + i, &i_var), get_variable(temp->value + i + 1, data));
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

/*
Return values
NULL - variable doesnt exist
any str - variable exists
status codes - ? detected
 */
char	*get_variable(char *var_str, t_data *data)
{
	char	*value;
	char	*extracted_var;
	int		var_name_len;

	var_name_len = 0;
	extracted_var = extract_var_without_symbol(var_str, &var_name_len);
	if (extracted_var[0] == '?')
	{
		free_ptr(extracted_var);
		return (ft_itoa(g_last_exit_code));
	}
	value = get_our_envp(data->our_envp, extracted_var);
	free_ptr(extracted_var);
	if (value)
		return (ft_strdup(value));
	else
		return (NULL);
}
