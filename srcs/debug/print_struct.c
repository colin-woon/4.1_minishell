/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:54:48 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/25 17:39:04 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens);
void	print_envp_array(t_data *data);

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
