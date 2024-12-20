/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:04:41 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/21 00:25:36 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, int type);
void	clear_tokens(t_token **head);
void	insert_token_node(t_token *prev_node, t_token *new_node);
void	delete_token(t_token **head, t_token *node_to_delete);
void	append_token(t_token **head, t_token *new_node);

t_token	*create_token(char *value, int type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_token(t_token **head, t_token *new_node)
{
	t_token *temp = *head;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void	delete_token(t_token **head, t_token *node_to_delete)
{
	if (!*head || !node_to_delete)
		return ;
	if (*head == node_to_delete)
		*head = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	free_ptr(node_to_delete->value);
	free_ptr(node_to_delete);
}

void	clear_tokens(t_token **head)
{
	t_token	*temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->value);
		free(temp);
	}
}

void	insert_token_node(t_token *prev_node, t_token *new_node)
{
	if (!prev_node || !new_node)
		return ;
	new_node->next = prev_node->next;
	new_node->prev = prev_node;
	if (prev_node->next)
		prev_node->next->prev = new_node;
	prev_node->next = new_node;
}
