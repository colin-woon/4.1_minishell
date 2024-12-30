/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:17:52 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/30 19:07:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr);
void	garbage_collector(t_data *data, char *input);

// Helps to avoid double frees
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	garbage_collector(t_data *data, char *input)
{
	if (data->envp_array)
	{
		ft_free_2d_array(data->envp_array);
		data->envp_array = NULL;
	}
	if (data->envp_origin)
		data->envp_origin = NULL;
	if (data->tokens)
		clear_tokens(&data->tokens);
	free_ptr(input);
}
