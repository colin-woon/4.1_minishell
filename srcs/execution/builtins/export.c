/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:30:57 by jow               #+#    #+#             */
/*   Updated: 2025/01/28 12:06:30 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** This function is used to get the key and value pair from the argument
** by 
*/
static char	*get_key_value_pair(char *arg)
{

}

int	check_valid_env_var(char *env_var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(env_var[i]) && env_var[i] != '_')
		return (EXIT_FAILURE);
	i++;
	while (env_var[i])
	{
		if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 1;
	if (!args[i])
		return (ft_env(data, args));
	while (args[i])
	{
		if (!check_valid_env_var(args[i]))
		{
			print_syntax_error(QUOTE_ERROR, args[i]);
			return (EXIT_FAILURE);
		}
		else if (ft_strchr(args[i], '='))
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			ft_free_2d_array(tmp);
		}
	}
	return (EXIT_SUCCESS);
}
