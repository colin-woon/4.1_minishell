/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_envp_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:07:49 by jow               #+#    #+#             */
/*   Updated: 2025/02/04 09:15:50 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*search_envp(t_envp *head, char *var_name);
void	delete_envp_node(t_envp **head, char *var_name);
void	append_envp(t_envp **head, t_envp *new_node);

void	append_envp(t_envp **head, t_envp *new_node)
{
	t_envp	*temp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void	delete_envp_node(t_envp **head, char *var_name)
{
	t_envp	*temp;

	if (!head || !*head || !var_name)
		return ;
	temp = *head;
	while (temp)
	{
		if (!ft_strncmp(temp->variable_name, var_name, ft_strlen(var_name)))
		{
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				*head = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			free(temp->variable_name);
			free(temp->value);
			free(temp);
			return ;
		}
		temp = temp->next;
	}
}

t_envp	*search_envp(t_envp *head, char *var_name)
{
	t_envp	*temp;

	temp = head;
	while (temp)
	{
		if (!ft_strncmp(temp->variable_name, var_name, ft_strlen(var_name))
			&& (ft_strlen(temp->variable_name) == ft_strlen(var_name)))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
