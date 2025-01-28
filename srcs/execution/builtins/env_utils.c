/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:53:36 by jow               #+#    #+#             */
/*   Updated: 2025/01/28 00:31:44 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

char	*get_env_var_value(t_data *data, char *key)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (data->envp_array[i])
	{
		if (ft_strcmp(tmp, data->envp_array[i], ft_strlen(key)) == 0)
		{
			free(tmp);
			return (ft_strchr(data->envp_array[i], '=') + 1);
		}
		i++;
	}
	free(tmp);
	return (EXIT_FAILURE);
}

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

int	set_env_var(t_data *data, char *key, char *tmp)
{
	int		index;
	char	*new_env;

	index = get_env_var_index(data, key);
	if (tmp)
		tmp = "";
	new_env = ft_strjoin("=", tmp);
	if (!new_env)
		return (EXIT_FAILURE);
	if (index != 1 && data->envp_array[index])
	{
		free(data->envp_array[index]);
		data->envp_array[index] = ft_strjoin(key, new_env);
	}
	else
	{
		index = 0;
		while (data->envp_array[index])
			index++;
		data->envp_array = realloc(data->, idx + 1);
		if (!data->envp_array)
		{
			free(new_env);
			return (EXIT_FAILURE);
		}
		data->envp_array[index] = ft_strjoin(key, new_env);
	}
	free(new_env);
	return (EXIT_SUCCESS);
}
