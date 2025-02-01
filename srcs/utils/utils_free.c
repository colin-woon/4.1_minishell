/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:17:52 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/01 18:08:33 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr);
void	garbage_collector(t_data *data, char *input, int is_clear_env_cache);
void	close_pipes(t_cmd *cmd, t_cmd *cmd_to_ignore);
void	close_fds(t_cmd *cmd, int is_restore_stdio);
void	exit_process(t_data *data, int exit_status);

// Helps to avoid double frees
void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	garbage_collector(t_data *data, char *input, int is_clear_env_cache)
{
	if (is_clear_env_cache)
	{
		// ft_free_2d_array(data->envp_array);
		// data->envp_array = NULL;
		rl_clear_history();
	}
	if (data->tokens)
		clear_tokens(&data->tokens);
	if (data->cmd)
		clear_cmd_list(&data->cmd);
	free_ptr(input);
}

void	close_fds(t_cmd *cmd, int is_restore_stdio)
{
	if (cmd->io_fds)
	{
		if (cmd->io_fds->fd_in != -1)
			close(cmd->io_fds->fd_in);
		if (cmd->io_fds->fd_out != -1)
			close(cmd->io_fds->fd_out);
		if (is_restore_stdio)
			restore_stdio(cmd->io_fds);
	}
	close_pipes(cmd, NULL);
}

void	close_pipes(t_cmd *cmd, t_cmd *cmd_to_ignore)
{
	while (cmd)
	{
		if (cmd != cmd_to_ignore && cmd->has_pipe)
		{
			close(cmd->pipe_fd[READ_END]);
			close(cmd->pipe_fd[WRITE_END]);
		}
		cmd = cmd->next;
	}
}

void	exit_process(t_data *data, int exit_status)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		garbage_collector(data, NULL, true);
	}
	exit(exit_status);
}
