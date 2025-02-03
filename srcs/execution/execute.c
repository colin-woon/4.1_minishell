/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:21 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/03 14:39:08 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *data);
int		execute_builtin(t_data *data, t_cmd *cmd);
int		execute_pipes(t_data *data);
void	execute_commands(t_data *data, t_cmd *cmd);
int		execute_binary(t_data *data, t_cmd *cmd);

void	execute(t_data *data)
{
	int	is_exit;

	is_exit = prepare_commands(data);
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
	g_last_exit_code = execute_pipes(data);
	return ;
}

int	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	is_not_exit;

	is_not_exit = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->name, "cd", ft_strlen("cd")) == 0)
		is_not_exit = ft_cd(data, cmd->args);
	else if (ft_strncmp(cmd->name, "echo", 5) == 0)
		is_not_exit = ft_echo(data, cmd->args);
	else if (ft_strncmp(cmd->name, "env", ft_strlen("env")) == 0)
		is_not_exit = ft_env(data, cmd->args);
	else if (ft_strncmp(cmd->name, "export", ft_strlen("export")) == 0)
		is_not_exit = ft_export(data, cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		is_not_exit = ft_pwd(data, cmd->args);
	else if (ft_strncmp(cmd->name, "unset", 6) == 0)
		is_not_exit = ft_unset(data, cmd->args);
	else if (ft_strncmp(cmd->name, "exit", 5) == 0)
		is_not_exit = ft_exit(data, 0);
	is_not_exit = 0;

	if (is_not_exit == 0)
		return (1);
	else
		return (is_not_exit);
}

int	execute_pipes(t_data *data)
{
	t_cmd	*cmd;
	int		process_exit_code;

	process_exit_code = -1;
	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			print_errno_str("fork", strerror(errno));
			return (errno);
		}
		else if (data->pid == 0)
			execute_commands(data, cmd);
		cmd = cmd->next;
	}
	process_exit_code = wait_cmds(data);
	return (process_exit_code);
}

void	execute_commands(t_data *data, t_cmd *cmd)
{
	int	exit_status;

	if (!cmd || !cmd->name || !is_valid_files(cmd->io_fds))
		exit_process(data, EXIT_FAILURE);
	setup_pipefds(data->cmd, cmd);
	redirect_stdio(cmd->io_fds);
	close_fds(cmd, false);
	if (ft_strchr(cmd->args[0], '/') )
	{
		exit_status = is_invalid_command(cmd);
		if (exit_status)
			exit_process(data, exit_status);
	}
	else
		get_cmd_path(data, cmd);
	exit_status = execute_builtin(data, cmd);
	if (exit_status != CMD_NOT_FOUND)
		exit_process(data, exit_status);
	exit_status = execute_binary(data, cmd);
	exit_process(data, exit_status);
}

int	execute_binary(t_data *data, t_cmd *cmd)
{
	int		exit_status;

	exit_status = is_invalid_command(cmd);
	if (exit_status == CMD_NOT_FOUND || exit_status == CMD_NOT_EXECUTABLE)
		return (exit_status);
	if (execve(cmd->args[0], cmd->args, data->envp_array) == -1)
	{
		print_errno_str("execve", strerror(errno));
		return (FAILURE);
	}
	return (FAILURE);
}
