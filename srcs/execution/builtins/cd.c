/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:02 by jow               #+#    #+#             */
/*   Updated: 2025/01/28 15:08:44 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_data *data, char **args);
char	*get_home_path(t_data *data);
int		change_dir(t_data *data, char *path);
void	ft_update_envlst(t_data *data, char *key, char *value);

void	ft_update_envlst(t_data *data, char *key, char *value)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data, "PWD"));
	set_env_var(data, "PWD", value);
	free(value);
}

int	change_dir(t_data *data, char *path)
{
	int	status;

	status = chdir(path);
	if (status == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	ft_update_envlst(data, "OLDPWD", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}

char	*get_home_path(t_data *data)
{
	int		i;
	char	*home;

	i = 0;
	while (data->envp_array[i])
	{
		if (!ft_strncmp(data->envp_array[i], "HOME=", 5))
		{
			home = ft_strdup(data->envp_array[i] + 5);
			return (home);
		}
		i++;
	}
	return (NULL);
}

int	ft_cd(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || args[1][0] == '\0')
	{
		path = get_home_path(data);
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (EXIT_FAILURE);
		}
		return (change_dir(data, path));
	}
	return (change_dir(data, args[1]));
}
