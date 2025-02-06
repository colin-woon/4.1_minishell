/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:02 by jow               #+#    #+#             */
/*   Updated: 2025/02/06 17:22:08 by jow              ###   ########.fr       */
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

	if (!args || !args[1] || args[1][0] == '\0' || !ft_strncmp(args[1], "~", 2))
	{
		tmp = search_envp(data->our_envp, "HOME");
		if (!tmp)
		{
			print_errno_str("cd", NULL, "HOME not set");
			return (EXIT_FAILURE);
		}
		return_value = change_dir(data, tmp->value);
		return (return_value);
	}
	return_value = change_dir(data, args[1]);
	return (return_value);
}
