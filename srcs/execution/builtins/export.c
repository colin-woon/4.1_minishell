/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:12:41 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/17 18:19:22 by jow              ###   ########.fr       */
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

/*
** Check if the argument is a valid environment variable
** - Must start with an alphabetic character or an underscore
** - Subsequent characters can be alphanumeric or an underscore
*/
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
	char	*keyword;

	keyword = get_keyword(arg);
	if (check_valid_env_var(arg) == EXIT_FAILURE)
	{
		print_errno_str("export", keyword,
			"not a valid identifier");
		free_ptr((void **)&keyword);
		return (EXIT_FAILURE);
	}
	if (ft_strchr(arg, '='))
	{
		tmp = search_envp(data->our_envp, keyword);
		if (!tmp)
			append_envp(&data->our_envp,
				create_envp_node(keyword, ft_strchr(arg, '=') + 1));
		else
			update_envp_value(data->our_envp, keyword,
				ft_strchr(arg, '=') + 1);
	}
	free_ptr((void **)&keyword);
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
