/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:41:03 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/10 14:55:54 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_cmd_path(t_envp *envp, t_cmd *cmd);
void	setup_pipefds(t_cmd *cmds_list, t_cmd *cmd_to_ignore);
int		is_invalid_command(t_cmd *cmd);
int		wait_cmds(t_data *data);

/*
when wait returns -1, it indicates error, and errno is set accordingly
ECHILD - no more child processes to wait
EINT - interrupted by signal

need to make sure all child processes are
 */
int	wait_cmds(t_data *data)
{
	int		exit_status;
	int		temp;
	pid_t	killed_child_pid;

	close_fds(data->cmd, false, data);
	temp = -1;
	killed_child_pid = 0;
	while (killed_child_pid != -1 || errno != ECHILD)
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

void	setup_pipefds(t_cmd *cmds_list, t_cmd *cmd_to_ignore)
{
	if (cmd_to_ignore->prev && cmd_to_ignore->prev->has_pipe)
		dup2(cmd_to_ignore->prev->pipe_fd[READ_END], STDIN_FILENO);
	if (cmd_to_ignore->has_pipe)
		dup2(cmd_to_ignore->pipe_fd[WRITE_END], STDOUT_FILENO);
	close_pipes(cmds_list, cmd_to_ignore);
}

int	get_cmd_path(t_envp *envp, t_cmd *cmd)
{
	char	**all_paths;
	char	*cmd_path;
	char	*absolute_path;
	int		i;

	i = -1;
	all_paths = ft_split(get_our_envp(envp, "PATH"), ':');
	if (all_paths == NULL)
		return (0);
	cmd_path = ft_strjoin("/", cmd->name);
	while (all_paths[++i])
	{
		absolute_path = ft_strjoin(all_paths[i], cmd_path);
		if (access(absolute_path, F_OK | X_OK) == 0)
		{
			free_ptr((void **)&cmd->args[0]);
			cmd->args[0] = ft_strdup(absolute_path);
			ft_free_2d_array(all_paths);
			return (free_ptr((void **)&cmd_path), \
			free_ptr((void **)&absolute_path), 1);
		}
		free_ptr((void **)&absolute_path);
	}
	return (ft_free_2d_array(all_paths), free_ptr((void **)&cmd_path), 0);
}

/*
if (!get_cmd_path(data, cmd))
{
	print_errno_str(cmd->args[0], strerror(errno));
	return (CMD_NOT_FOUND);
}
*/
int	is_invalid_command(t_cmd *cmd)
{
	struct stat	path_stat;

	if (stat(cmd->args[0], &path_stat) != 0)
	{
		print_errno_str(cmd->args[0], NULL, strerror(errno));
		return (CMD_NOT_FOUND);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		print_errno_str(cmd->args[0], NULL, "Is a directory");
		return (CMD_NOT_EXECUTABLE);
	}
	if (access(cmd->args[0], X_OK) != 0)
	{
		print_errno_str(cmd->args[0], NULL, strerror(errno));
		return (CMD_NOT_EXECUTABLE);
	}
	return (0);
}
