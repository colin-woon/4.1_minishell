/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:02 by jow               #+#    #+#             */
/*   Updated: 2025/02/05 20:10:46 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_data *data, char **args);
int		change_dir(t_data *data, char *path);

int	change_dir(t_data *data, char *path)
{
	int		status;
	char	*new_pwd;

	status = chdir(path);
	if (status == -1)
	{
		print_errno_str("cd", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	update_envp_value(data->our_envp, "OLDPWD", \
		get_our_envp(data->our_envp, "PWD"));
	new_pwd = getcwd(NULL, 0);
	update_envp_value(data->our_envp, "PWD", new_pwd);
	data->envp_array = convert_envp(data, data->our_envp);
	free_ptr((void **)&new_pwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_data *data, char **args)
{
	t_envp	*tmp;
	int		return_value;

	if (!args || !args[1] || args[1][0] == '\0')
	{
		tmp = search_envp(data->our_envp, "HOME");
		if (!tmp)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (EXIT_FAILURE);
		}
		return_value = change_dir(data, tmp->value);
		return (return_value);
	}
	return_value = change_dir(data, args[1]);
	return (return_value);
}
