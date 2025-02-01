/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:28:06 by jow               #+#    #+#             */
/*   Updated: 2025/02/02 02:07:46 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_envp(t_envp *envp) {
	int i;
	t_envp *temp;
	char **envp_array;
	char *env_var;

	i = 0;
	temp = envp;
	while (temp) {
		i++;
		temp = temp->next;
	}
	envp_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_array)
		return NULL;
	temp = envp;
	i = 0;
	while (temp)
	{
		env_var = ft_strjoin(temp->variable_name, "=");
		envp_array[i] = ft_strjoin(env_var, temp->value);
		free(env_var);
		if (!envp_array[i])
		{
			while (i > 0)
				free(envp_array[--i]);
			free(envp_array);
			return NULL;
		}
		temp = temp->next;
		i++;
	}
	envp_array[i] = NULL;
	return envp_array;
}
