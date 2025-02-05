/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:17:36 by jow               #+#    #+#             */
/*   Updated: 2025/02/05 20:09:50 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_cmd(t_cmd *cmd, void (*del)(void **));
void	clear_cmd_list(t_cmd **head);
t_cmd	*get_last_cmd(t_cmd *cmd);

void	delete_cmd(t_cmd *cmd, void (*del)(void **))
{
	if (cmd->name)
		(*del)((void **)&cmd->name);
	if (cmd->args)
		ft_free_2d_array(cmd->args);
	if (cmd->io_fds)
		free_io_fds(cmd->io_fds);
	(*del)((void **)&cmd);
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
