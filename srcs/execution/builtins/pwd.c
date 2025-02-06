/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:20:39 by jow               #+#    #+#             */
/*   Updated: 2025/02/06 17:07:21 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args);

int	ft_pwd(char **args)
{
	char	*cwd;

	if (args[1])
	{
		print_errno_str("pwd", args[1], "invalid option");
		ft_print_string("pwd: usage: pwd [-LP]\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, 1);
	free_ptr((void **)&cwd);
	return (0);
}
