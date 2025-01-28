/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:20:39 by jow               #+#    #+#             */
/*   Updated: 2025/01/27 20:28:03 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *data);

int	ft_cd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}
