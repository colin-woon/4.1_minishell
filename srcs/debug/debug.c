/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:30:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/09 15:32:37 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_tokens(t_token *tokens);
// void	print_envp_array(t_data *data);
// void	print_value_str(char *message, char *value);
// void	print_value_int(char *message, int value);
// void	print_value_char(char *message, char value);
// void	print_cmd(t_cmd *cmd);
// void	print_all_cmds(t_cmd *head);
// void	print_io_fds(t_io_fds *io_fds);
// void	print_envp_list(t_envp *head);

// void	print_envp_array(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (!data->envp_array)
// 	{
// 		printf("envp_array is NULL\n");
// 		return;
// 	}
// 	while (data->envp_array[i])
// 	{
// 		printf("%s\n", data->envp_array[i]);
// 		i++;
// 	}
// }

// void	print_tokens(t_token *tokens)
// {
// 	t_token *current = tokens;
// 	while (current)
// 	{
// 		printf("Value: %s, Type: %d\n", current->value, current->type);
// 		current = current->next;
// 	}
// }

// void	print_value_str(char *message, char *value)
// {
// 	printf("%s %s\n", message, value);
// }

// void	print_value_int(char *message, int value)
// {
// 	printf("%s %d\n", message, value);
// }

// void	print_value_char(char *message, char value)
// {
// 	printf("%s %c\n", message, value);
// }

// void	print_io_fds(t_io_fds *io_fds)
// {
// 	if (!io_fds)
// 	{
// 		printf("io_fds is NULL\n");
// 		return;
// 	}

// 	if (io_fds->infile)
// 		print_value_str("infile:", io_fds->infile);
// 	else
// 		print_value_str("infile:", "(null)");

// 	if (io_fds->outfile)
// 		print_value_str("outfile:", io_fds->outfile);
// 	else
// 		print_value_str("outfile:", "(null)");

// 	if (io_fds->heredoc_limiter)
// 		print_value_str("heredoc_limiter:", io_fds->heredoc_limiter);
// 	else
// 		print_value_str("heredoc_limiter:", "(null)");

// 	print_value_int("is_heredoc_quotes:", io_fds->is_heredoc_quotes);
// 	print_value_int("fd_in:", io_fds->fd_in);
// 	print_value_int("fd_out:", io_fds->fd_out);
// }

// void	print_cmd(t_cmd *cmd)
// {
// 	if (!cmd)
// 	{
// 		printf("cmd is NULL\n");
// 		return;
// 	}
// 	print_value_str("name:", cmd->name ? cmd->name : "(null)");
// 	print_value_str("path:", cmd->path ? cmd->path : "(null)");

// 	if (cmd->args)
// 	{
// 		int i = 0;
// 		printf("args:\n");
// 		while (cmd->args[i])
// 		{
// 			printf("  [%d]: %s\n", i, cmd->args[i]);
// 			i++;
// 		}
// 	}
// 	print_value_int("has_pipe:", cmd->has_pipe);
// }

// void	print_all_cmds(t_cmd *head)
// {
// 	t_cmd *current = head;
// 	int i = 0;

// 	while (current)
// 	{
// 		print_value_int("COMMAND", i);
// 		print_cmd(current);
// 		printf("\n");
// 		current = current->next;
// 		i++;
// 	}
// }

// void	print_envp_list(t_envp *head)
// {
// 	t_envp	*temp;

// 	temp = head;
// 	while (temp)
// 	{
// 		print_value_str("Variable is", temp->variable_name);
// 		print_value_str("Value is", temp->value);
// 		temp = temp->next;
// 	}
// }
