/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:55:09 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/03 14:36:29 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_our_envp(t_envp *envp, char *variable_name);
t_envp	*create_envp_node(char *var_name, char *value);
void	clear_envp_list(t_envp **head);
void	update_envp_value(t_envp *head, char *var_name, char *new_value);
t_envp	*search_envp(t_envp *head, char *var_name);
void	delete_envp_node(t_envp **head, char *var_name);
void	append_envp(t_envp **head, t_envp *new_node);
char	**convert_envp(t_data *data, t_envp *envp);

char	**convert_envp(t_data *data, t_envp *envp)
{
	int		i;
	t_envp	*temp;
	char	**envp_array;
	char	*env_var;

	if (data->envp_array)
		ft_free_2d_array(data->envp_array);
	i = 0;
	temp = envp;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	envp_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_array)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp)
	{
		env_var = ft_strjoin(temp->variable_name, "=");
		envp_array[i] = ft_strjoin(env_var, temp->value);
		free(env_var);
		if (!envp_array[i])
		{
			ft_free_2d_array(envp_array);
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

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

char	*get_our_envp(t_envp *envp, char *variable_name)
{
	t_envp *temp;

	temp = envp;
	temp = search_envp(temp, variable_name);
	return (temp->value);
}
