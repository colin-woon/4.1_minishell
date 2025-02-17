/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:55:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/17 18:21:30 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_our_envp(t_envp *envp, char *variable_name);
t_envp	*create_envp_node(char *var_name, char *value);
void	clear_envp_list(t_envp **head);
void	update_envp_value(t_envp *head, char *var_name, char *new_value);

t_envp	*create_envp_node(char *var_name, char *value)
{
	t_envp	*new_node;

	new_node = (t_envp *)malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->variable_name = ft_strdup(var_name);
	new_node->value = ft_strdup(value);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

/*
	Update the value of an existing node in the envp list
*/
void	update_envp_value(t_envp *head, char *var_name, char *new_value)
{
	t_envp	*node;

	node = search_envp(head, var_name);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(new_value);
	}
}

void	clear_envp_list(t_envp **head)
{
	t_envp	*current;
	t_envp	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->variable_name);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}

/*
** Search for a variable(var_name) in the ENVP LIST
*/
char	*get_our_envp(t_envp *envp, char *variable_name)
{
	t_envp	*temp;

	temp = envp;
	temp = search_envp(temp, variable_name);
	if (temp)
		return (temp->value);
	else
		return (NULL);
}
