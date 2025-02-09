/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:06:14 by jow               #+#    #+#             */
/*   Updated: 2025/02/09 14:57:42 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_argc(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	ft_atoull(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

static int	get_exit_code(t_data *data, char *arg)
{
	int					i;
	unsigned long long	exit_code;

	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			print_errno_str("exit", arg, "numeric argument required");
			exit_process(data, 2);
		}
		i++;
	}
	exit_code = ft_atoull(arg);
	return ((int)exit_code % 256);
}

int	ft_exit(t_data *data, char **args)
{
	int	exit_code;
	int	argc;

	if (args == NULL)
		argc = 0;
	else
		argc = ft_get_argc(args);
	if (argc > 2)
	{
		print_errno_str("exit", NULL, "too many arguments");
		return (1);
	}
	ft_putendl_fd("exit", 1);
	if (argc == 2)
		exit_code = get_exit_code(data, args[1]);
	else
		exit_code = data->last_exit_code;
	exit_process(data, exit_code);
	return (0);
}
