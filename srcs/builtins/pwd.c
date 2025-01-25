/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:20:39 by jow               #+#    #+#             */
/*   Updated: 2025/01/25 14:30:17 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	current_directory(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_last_exit_code = 1;
		return (1);
	}
	ft_putendl_fd(cwd, data->std_fds[STDOUT]);
	free(cwd);
	return (0);
}
