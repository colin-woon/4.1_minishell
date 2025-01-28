/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:52:30 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/27 18:28:46 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_data(t_data *data, char **envp);
void	init_env(t_data *data, char **envp);

void	init_shell_data(t_data *data, char **envp)
{
	init_env(data, envp);
	data->envp_origin = envp;
	data->cmd = NULL;
	data->pid = -1;
	g_last_exit_code = 0;
}

void	init_env(t_data *data, char **envp)
{
	int	total_env;
	int	i;

	total_env = 0;
	while (envp && envp[total_env])
		total_env++;
	data->envp_array = ft_calloc(total_env + 1, sizeof(char *));
	if (data->envp_array == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		data->envp_array[i] = ft_strdup(envp[i]);
		if (data->envp_array[i] == NULL)
			return ;
		i++;
	}
}

