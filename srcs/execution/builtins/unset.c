/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:53:59 by jow               #+#    #+#             */
/*   Updated: 2025/02/08 15:35:29 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, char **args);

int	ft_unset(t_data *data, char **args)
{
	int		i;
	int		ret;
	t_envp	*tmp;

	i = 1;
	ret = 0;
	while (args[i])
	{
		if (check_valid_env_var(args[i]) == EXIT_FAILURE)
		{
			print_errno_str("unset", args[i],
				"not a valid identifier");
			ret = 1;
		}
		tmp = search_envp(data->our_envp, args[i]);
		if (tmp)
			delete_envp_node(&data->our_envp, args[i]);
		i++;
	}
	data->envp_array = convert_envp(data, data->our_envp);
	return (ret);
}
