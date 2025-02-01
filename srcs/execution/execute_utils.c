/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:28:06 by jow               #+#    #+#             */
/*   Updated: 2025/02/02 01:41:04 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_envp(t_envp *envp)
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
	char **envp_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_array)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp)
	{
		envp_array[i] = ft_strdup(temp->variable_name);
		temp = temp->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}
