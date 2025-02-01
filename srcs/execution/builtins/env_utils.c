/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:53:36 by jow               #+#    #+#             */
/*   Updated: 2025/01/28 15:29:56 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_env_var_value(t_data *data, char *key)
// {
// 	int		i;
// 	char	*tmp;

// 	tmp = ft_strjoin(key, "=");
// 	if (!tmp)
// 		return (NULL);
// 	i = 0;
// 	while (data->envp_array[i])
// 	{
// 		if (ft_strcmp(tmp, data->envp_array[i], ft_strlen(key)) == 0)
// 		{
// 			free(tmp);
// 			return (ft_strchr(data->envp_array[i], '=') + 1);
// 		}
// 		i++;
// 	}
// 	free(tmp);
// 	return (EXIT_FAILURE);
// }

int	get_env_var_index(t_data *data, char *key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (data->envp_array[i])
	{
		// print_value_str("data->envp_array[i]: ", data->envp_array[i]);
		if (!ft_strncmp(data->envp_array[i], key, key_len) && data->envp_array[i][key_len] == '=')
			return (i);
		i++;
	}
	return (EXIT_FAILURE);
}

int	set_env_var(t_data *data, char *key, char *tmp)
{
	int		i;

	i = get_env_var_index(data, key);
	data->envp_array[i] = replace_substring(data->envp_array[i], getenv(key), tmp);
	if (!data->envp_array[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
