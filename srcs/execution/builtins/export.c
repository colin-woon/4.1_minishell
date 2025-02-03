/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:12:41 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/03 13:13:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_export(t_data *data, char **args);
int			check_valid_env_var(char *env_var);
static char	*get_keyword(char *arg);
static int	handle_export_var(t_data *data, char *arg);

static char	*get_keyword(char *arg)
{
	char	*keyword;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	keyword = ft_substr(arg, 0, i);
	return (keyword);
}

int	check_valid_env_var(char *env_var)
{
	int	i;

	if (!env_var || !env_var[0])
		return (EXIT_FAILURE);
	if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
		return (EXIT_FAILURE);
	i = 1;
	while (env_var[i] && env_var[i] != '=')
	{
		if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	handle_export_var(t_data *data, char *arg)
{
	t_envp	*tmp;

	if (check_valid_env_var(arg) == EXIT_FAILURE)
	{
		print_errno_str("export", get_keyword(arg), "not a valid identifier");
		return (EXIT_FAILURE);
	}
	if (ft_strchr(arg, '='))
	{
		tmp = search_envp(data->our_envp, get_keyword(arg));
		if (!tmp)
			append_envp(&data->our_envp,
				create_envp_node(get_keyword(arg), ft_strchr(arg, '=') + 1));
		else
			update_envp_value(data->our_envp, get_keyword(arg),
				ft_strchr(arg, '=') + 1);
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *data, char **args)
{
	int	i;

	i = 1;
	if (!args[i])
		return (ft_env(data, args));
	while (args[i])
	{
		if (handle_export_var(data, args[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	data->envp_array = convert_envp(data, data->our_envp);
	return (EXIT_SUCCESS);
}
