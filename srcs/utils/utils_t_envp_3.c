/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_envp_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 08:32:57 by jow               #+#    #+#             */
/*   Updated: 2025/02/05 20:10:46 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**convert_envp(t_data *data, t_envp *envp);
static char	**join_env_var(char **envp_array, t_envp *envp);
static int	count_envp(t_envp *envp);

static char	**join_env_var(char **envp_array, t_envp *envp)
{
	t_envp	*temp;
	char	*env_var;
	int		i;

	i = 0;
	temp = envp;
	while (temp)
	{
		env_var = ft_strjoin(temp->variable_name, "=");
		envp_array[i] = ft_strjoin(env_var, temp->value);
		free_ptr((void **)&env_var);
		if (!envp_array[i])
		{
			ft_free_2d_array(envp_array);
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

static int	count_envp(t_envp *envp)
{
	int		i;
	t_envp	*temp;

	i = 0;
	temp = envp;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	**convert_envp(t_data *data, t_envp *envp)
{
	int		i;
	char	**envp_array;

	if (data->envp_array)
		ft_free_2d_array(data->envp_array);
	i = count_envp(envp);
	envp_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_array)
		return (NULL);
	envp_array = join_env_var(envp_array, envp);
	return (envp_array);
}
