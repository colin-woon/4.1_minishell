/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:20:39 by jow               #+#    #+#             */
/*   Updated: 2025/02/11 00:47:05 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args);

int	ft_pwd(char **args)
{
	char	*cwd;
	char	option[3];

	if (args[1] && args[1][0] == '-')
	{
		option[0] = '-';
		option[1] = args[1][1];
		option[2] = '\0';
		print_errno_str("pwd", option, "invalid option");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, 1);
	free_ptr((void **)&cwd);
	return (0);
}
