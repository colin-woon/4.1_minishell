/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:50:34 by jow               #+#    #+#             */
/*   Updated: 2025/02/03 13:51:39 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args);

int	ft_env(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
	{
		print_errno_builtin("env", args[1], "No such file or directory");
		return (EXIT_FAILURE);
	}
	if (!data->envp_array)
		return (EXIT_FAILURE);
	while (data->envp_array[i])
	{
		ft_putendl_fd(data->envp_array[i], 1);
		i++;
	}
	return (EXIT_SUCCESS);
}
