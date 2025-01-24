/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parse_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:41:05 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/24 13:41:22 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_pipe(t_cmd **cmd, t_token **current_tokens);

void	parse_pipe(t_cmd **cmd, t_token **current_tokens)
{
	t_cmd	*last_cmd;

	last_cmd = get_last_cmd(*cmd);
	last_cmd->has_pipe = 1;
	append_cmd(&last_cmd, create_cmd());
	*current_tokens = (*current_tokens)->next;
}
