/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:02 by jow               #+#    #+#             */
/*   Updated: 2025/02/03 02:09:12 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(t_data *data, char **args);
int		change_dir(t_data *data, char *path);

int	change_dir(t_data *data, char *path)
{
	int		status;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_our_envp(data->our_envp, "PWD");
	printf("Debug - Attempting to cd to: %s\n", path);
    printf("Debug - Current directory: %s\n", oldpwd);
	status = chdir(path);
	if (status == -1)
	{
		print_errno_str("cd", path, strerror(errno));
		return (EXIT_FAILURE);
	}
	newpwd = getcwd(NULL, 0);
	printf("Debug - New directory: %s\n", newpwd);
	update_envp_value(data->our_envp, "OLDPWD", oldpwd);
	update_envp_value(data->our_envp, "PWD", newpwd);
	data->envp_array = convert_envp(data, data->our_envp);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_data *data, char **args)
{
	t_envp	*tmp;
	int		return_value;

	printf("im in cd\n");
	if (!args || !args[1] || args[1][0] == '\0')
	{
		tmp = search_envp(data->our_envp, "HOME");
		printf("Debug - args[1]: %s\n", args[1] ? args[1] : "NULL");
		if (tmp)
			printf("Debug - HOME value: %s\n", tmp->value);
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
