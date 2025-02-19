/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:11:12 by jow               #+#    #+#             */
/*   Updated: 2025/02/17 18:16:41 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *data, char **args);

/*
** The echo builtin writes any specified operands, separated by a single space
	=> if (args[i + 1] && args[i + 1][0])
	- to check if the next argument is not NULL
	- Handles cases like:
		- echo Hello $BIGBIG123 world
		- will output "Hello world" instead of "Hello  world"
*/
int	ft_echo(t_data *data, char **args)
{
	int	i;
	int	n_flag;

	(void)data;
	i = 1;
	n_flag = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i + 1][0])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
