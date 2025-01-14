/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:48 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/14 17:01:21 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens);
void	print_envp_array(t_data *data);
void	print_value_str(char *message, char *value);
void	print_value_int(char *message, int value);
void	print_value_char(char *message, char value);

void	print_envp_array(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp_array[i])
	{
		printf("%s\n", data->envp_array[i]);
		i++;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	while (current)
	{
		printf("Value: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	print_value_str(char *message, char *value)
{
	printf("%s %s\n", message, value);
}

void	print_value_int(char *message, int value)
{
	printf("%s %d\n", message, value);
}

void	print_value_char(char *message, char value)
{
	printf("%s %c\n", message, value);
}
