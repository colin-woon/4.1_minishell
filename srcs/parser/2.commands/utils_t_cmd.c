/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:42:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/24 19:16:58 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd();
void	prepend_cmd(t_cmd **head, t_cmd *new_cmd);
void	append_cmd(t_cmd **head, t_cmd *new_cmd);
void	delete_cmd(t_cmd *cmd, void (*del)(void *));
void	clear_cmd_list(t_cmd **head);
t_cmd	*get_last_cmd(t_cmd *cmd);

t_cmd	*create_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	return (new_cmd);
}

void	append_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!head || !new_cmd)
		return;
	if (!*head)
	{
		*head = new_cmd;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
	new_cmd->prev = temp;
}

void	prepend_cmd(t_cmd **head, t_cmd *new_cmd)
{
	if (!head || !new_cmd)
		return;
	if (*head)
	{
		new_cmd->next = *head;
		(*head)->prev = new_cmd;
	}
	*head = new_cmd;
}

void	clear_cmd_list(t_cmd **head)
{
	t_cmd	*temp;
	t_cmd	*next;

	if (!head)
		return;
	temp = *head;
	while (temp)
	{
		next = temp->next;
		delete_cmd(temp, &free_ptr);
		temp = next;
	}
	*head = NULL;
}

void	delete_cmd(t_cmd *cmd, void (*del)(void *))
{
	if (cmd->name)
		(*del)(cmd->name);
	if (cmd->args)
		ft_free_2d_array(cmd->args);
	if (cmd->pipe_fd)
		(*del)(cmd->pipe_fd);
	if (cmd->io_fds)
		free_io_fds(cmd->io_fds);
	(*del)(cmd);
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
