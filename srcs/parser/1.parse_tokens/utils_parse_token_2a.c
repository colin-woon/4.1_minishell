/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2a.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:01:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/17 18:46:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		substitute_variable(t_data *data, t_token **token_list);
char		*get_variable(char *var_str, t_data *data);
int			replace_variable(t_token *token_node, char *variable_name, \
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
				if (is_valid_variable(temp->value, i, is_quote))
					i += replace_variable(temp, extract_var(temp->value + i, true), get_variable(temp->value + i, data));
				else
					i++;
			}
		}
		temp = temp->next;
	}
}

/*
No quote or double quote will substitute variable
 */
int	is_valid_variable(char *value, int i, int is_quote)
{
	if (value[i] == '$'
		&& !is_next_invalid(value[i + 1], true)
		&& !is_symbol_only_in_quotes(value, i)
		&& (!is_quote || is_quote == DOUBLE_QUOTE))
		return (1);
	return (0);
}

/*
IF get_variable is NULL, remove the variable_name
eg: "$FAKE" > "" (reduced to atoms)
ELSE
	substitute dat thang
 */
int	replace_variable(t_token *token_node, char *variable_name, \
char *variable_result)
{
	int to_increment;

	to_increment = 1;
	// printf("HELLO\n");
	if (variable_result)
	// {
		token_node->value = replace_substring(token_node->value, \
			variable_name, variable_result);
	// to_increment = ft_strlen(variable_result);
	// }
	else
		remove_substring(token_node->value, variable_name);
	free_ptr((void **)&variable_name);
	free_ptr((void **)&variable_result);
	return (to_increment);
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

	extracted_var = extract_var(var_str, false);
	if (!ft_strncmp(extracted_var, "$?", 2))
	{
		free_ptr((void **)&extracted_var);
		return (ft_itoa(data->last_exit_code));
	}
	value = get_our_envp(data->our_envp, extracted_var);
	free_ptr((void **)&extracted_var);
	if (value)
		return (ft_strdup(value));
	else
		return (NULL);
}
