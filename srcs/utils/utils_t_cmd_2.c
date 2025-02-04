/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:17:36 by jow               #+#    #+#             */
/*   Updated: 2025/02/04 09:24:19 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_cmd(t_cmd *cmd, void (*del)(void *));
void	clear_cmd_list(t_cmd **head);
t_cmd	*get_last_cmd(t_cmd *cmd);

void	delete_cmd(t_cmd *cmd, void (*del)(void *))
{
	if (cmd->name)
		(*del)(cmd->name);
	if (cmd->args)
		ft_free_2d_array(cmd->args);
	if (cmd->io_fds)
		free_io_fds(cmd->io_fds);
	(*del)(cmd);
}

void	clear_cmd_list(t_cmd **head)
{
	t_cmd	*temp;
	t_cmd	*next;

	if (!head)
		return ;
	temp = *head;
	while (temp)
	{
		next = temp->next;
		delete_cmd(temp, &free_ptr);
		temp = next;
	}
	*head = NULL;
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
