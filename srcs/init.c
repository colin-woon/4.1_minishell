/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:52:30 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/04 15:44:47 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_data(t_data *data, char **envp);
void	init_envp(t_data *data, char **envp);

void	init_shell_data(t_data *data, char **envp)
{
	init_envp(data, envp);
	data->pid = -1;
	g_last_exit_code = 0;
}

void	init_envp(t_data *data, char **envp)
{
	int		i;
	char	**key_value;

	i = 0;
	while (envp[i])
	{
		key_value = ft_split(envp[i], '=');
		append_envp(&data->our_envp, \
		create_envp_node(key_value[0], key_value[1]));
		ft_free_2d_array(key_value);
		i++;
	}
	data->envp_array = convert_envp(data, data->our_envp);
}
