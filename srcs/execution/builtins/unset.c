/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:53:59 by jow               #+#    #+#             */
/*   Updated: 2025/02/03 14:03:44 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char **args);

int	ft_unset(t_data *data, char **args)
{
	int		i;
	t_envp	*tmp;

	i = 1;
	while (args[i])
	{
		tmp = search_envp(data->our_envp, args[i]);
		if (tmp)
			delete_envp_node(&data->our_envp, args[i]);
		i++;
	}
	data->envp_array = convert_envp(data, data->our_envp);
	return (EXIT_SUCCESS);
}
