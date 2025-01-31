/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:21 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/31 16:50:56 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *data);
int		execute_builtin(t_data *data, t_cmd *cmd);
int		execute_pipes(t_data *data);
void	execute_commands(t_data *data, t_cmd *cmd);
int		execute_binary(t_data *data, t_cmd *cmd);
int	get_cmd_path(t_data *data, t_cmd *cmd);
void	setup_pipefds(t_cmd *cmds_list, t_cmd *cmd_to_ignore);
int		is_invalid_command(t_cmd *cmd);
int		wait_cmds(t_data *data);

void	execute(t_data *data)
{
	int	is_exit;

	is_exit = validate_commands(data);
	if (is_exit)
		return ;
	// if (!data->cmd->has_pipe && !data->cmd->prev \
	// && is_valid_files(data->cmd->io_fds))
	// {
	// 	redirect_stdio(data->cmd->io_fds);
	// 	is_exit = execute_builtin(data, data->cmd);
	// 	restore_stdio(data->cmd->io_fds);
	// }
	// if (is_exit)
	// 	return ;
	g_last_exit_code = execute_pipes(data);
	return ;
}
int	execute_builtin(t_data *data, t_cmd *cmd)
{
	int	is_not_exit;

	is_not_exit = CMD_NOT_FOUND;
	// if (ft_strncmp(cmd->name, "cd", 3) == 0)
	// 	ft_cd(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "echo", 5) == 0)
	// 	is_not_exit = echo_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "env", 4) == 0)
	// 	is_not_exit = env_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "export", 7) == 0)
	// 	is_not_exit = export_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "pwd", 4) == 0)
	// 	is_not_exit = pwd_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "unset", 6) == 0)
	// 	is_not_exit = unset_builtin(data, cmd->args);
	// else if (ft_strncmp(cmd->name, "exit", 5) == 0)
	// 	is_not_exit = exit_builtin(data, cmd->args);
	// is_not_exit = 0;
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

int	wait_cmds(t_data *data)
{
	int		exit_status;
	int		temp;
	pid_t	killed_child_pid;

	close_fds(data->cmd, false);
	temp = -1;
	killed_child_pid = 0;
	while (killed_child_pid != -1)
	{
		if (killed_child_pid == data->pid)
			temp = exit_status;
		killed_child_pid = wait(&exit_status);
	}
	if (WIFSIGNALED(temp))
		exit_status = 128 + WTERMSIG(temp);
	else if (WIFEXITED(temp))
		exit_status = WEXITSTATUS(temp);
	else
		exit_status = temp;
	return (exit_status);
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

void	setup_pipefds(t_cmd *cmds_list, t_cmd *cmd_to_ignore)
{
	if (cmd_to_ignore->prev && cmd_to_ignore->prev->has_pipe)
		dup2(cmd_to_ignore->prev->pipe_fd[READ_END], STDIN_FILENO);
	if (cmd_to_ignore->has_pipe)
		dup2(cmd_to_ignore->pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipes(cmds_list, cmd_to_ignore);
}

int	get_cmd_path(t_data *data, t_cmd *cmd)
{
	char	**all_paths;
	char	*cmd_path;
	char	*absolute_path;
	int		i;

	i = -1;
	all_paths = ft_split(getenv("PATH"), ':');
	if (all_paths == NULL)
		return (0);
	cmd_path = ft_strjoin("/", cmd->name);
	while (all_paths[++i])
	{
		absolute_path = ft_strjoin(all_paths[i], cmd_path);
		if (access(absolute_path, F_OK | X_OK) == 0)
		{
			free_ptr(cmd->args[0]);
			cmd->args[0] = ft_strdup(absolute_path);
			ft_free_2d_array(all_paths);
			return (free_ptr(cmd_path), free_ptr(absolute_path), 1);
		}
		free_ptr(absolute_path);
	}
	return (ft_free_2d_array(all_paths), free_ptr(cmd_path), 0);
}

int	is_invalid_command(t_cmd *cmd)
{
	struct stat	path_stat;

	// if (!get_cmd_path(data, cmd))
	// {
	// 	print_errno_str(cmd->args[0], strerror(errno));
	// 	return (CMD_NOT_FOUND);
	// }
	if (stat(cmd->args[0], &path_stat) != 0)
	{
		print_errno_str(cmd->args[0], strerror(errno));
		return (CMD_NOT_FOUND);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		print_errno_str(cmd->args[0], "Is a directory");
		return (CMD_NOT_EXECUTABLE);
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		print_errno_str(cmd->args[0], strerror(errno));
		return (CMD_NOT_EXECUTABLE);
	}
	return (0);
}

int	execute_binary(t_data *data, t_cmd *cmd)
{
	int	exit_status;

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
