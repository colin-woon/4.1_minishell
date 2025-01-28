/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:21 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/28 12:38:27 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_data *data);
int		execute_builtin(t_data *data, t_cmd *cmd);

void	execute_commands(t_data *data)
{
	int	is_exit;

	is_exit = validate_commands(data);
	if (is_exit)
		return ;
	if (!data->cmd->has_pipe && !data->cmd->prev \
	&& is_valid_files(data->cmd->io_fds))
	{
		redirect_stdio(data->cmd->io_fds);
		is_exit = execute_builtin(data, data->cmd);
		restore_stdio(data->cmd->io_fds);
	}
	if (is_exit)
		return ;
	// return (create_children(data));
}
int	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	is_exit;

	is_exit = 1;
	if (ft_strncmp(cmd->name, "cd", 3) == 0)
		ft_cd(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "echo", 5) == 0)
	// 	is_exit = echo_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "env", 4) == 0)
	// 	is_exit = env_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "export", 7) == 0)
	// 	is_exit = export_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
	// 	is_exit = pwd_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "unset", 6) == 0)
	// 	is_exit = unset_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "exit", 5) == 0)
	// 	is_exit = exit_builtin(data, cmd->args);
	return (is_exit);
}
