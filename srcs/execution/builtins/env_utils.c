/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:53:36 by jow               #+#    #+#             */
/*   Updated: 2025/02/01 16:38:26 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env_var(t_data *data, char *key, char *tmp);
int	get_env_var_index(t_data *data, char *key);

int	get_env_var_index(t_data *data, char *key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (data->envp_array[i])
	{
		if (!ft_strncmp(data->envp_array[i], key, key_len) && data->envp_array[i][key_len] == '=')
			return (i);
		i++;
	}
	return (EXIT_FAILURE);
}

// int	set_env_var(t_data *data, char *key, char *tmp)
// {
// 	int		i;

// 	i = get_env_var_index(data, key);
// 	data->envp_array[i] = replace_substring(data->envp_array[i], getenv(key), tmp);
// 	if (!data->envp_array[i])
// 		return (EXIT_FAILURE);
// 	if (i != 1 && data->envp_array[i])
// 	{
// 		free(data->envp_array[i]);
// 		data->envp_array[i] = ft_strjoin(key, new_env);
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (data->envp_array[i])
// 			i++;
// 		data->envp_array = realloc(data->envp_array, i + 1);
// 		if (!data->envp_array)
// 		{
// 			free(new_env);
// 			return (EXIT_FAILURE);
// 		}
// 		data->envp_array[i] = ft_strjoin(key, new_env);
// 	}
// 	free(new_env);
// 	return (EXIT_SUCCESS);
// }
