/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:52:30 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/20 15:53:30 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_data(t_data *data, char **envp);
void	init_env(t_data *data, char **envp);
void	init_stdfds(t_data *data);

void	init_shell_data(t_data *data, char **envp)
{
	init_env(data, envp);
	init_stdfds(data);
	data->envp_origin = envp;
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

void	init_stdfds(t_data *data)
{
	data->std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	data->std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	data->std_fds[STDERR_FILENO] = dup(STDERR_FILENO);
}
