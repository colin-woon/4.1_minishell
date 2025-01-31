/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:21 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/31 14:14:59 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *data);
int		execute_builtin(t_data *data, t_cmd *cmd);
int		execute_pipes(t_data *data);
void	execute_commands(t_data *data, t_cmd *cmd);
int		wait_cmds(t_data *data);

void	execute(t_data *data)
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
	g_last_exit_code = execute_pipes(data);
	return ;
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

int	execute_pipes(t_data *data)
{
	t_cmd	*cmd;
	int		process_exit_code;

	process_exit_code = -1;
	cmd = data->cmd;
	while (data->pid != -1 && cmd)
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
	if (!cmd || !cmd->name || !is_valid_files(cmd->io_fds))
		exit_process(data, EXIT_FAILURE);
	setup_pipefds(data->cmd, cmd);
	redirect_stdio(cmd->io_fds);
	close_fds(cmd, false);

}

void	setup_pipefds(t_cmd *cmds_list, t_cmd *cmd_to_ignore)
{
	if (cmd_to_ignore->prev && cmd_to_ignore->prev->has_pipe)
		dup2(cmd_to_ignore->prev->pipe_fd[READ_END], STDIN_FILENO);
	if (cmd_to_ignore->has_pipe)
		dup2(cmd_to_ignore->pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipes(cmds_list, cmd_to_ignore);
}
