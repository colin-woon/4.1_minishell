/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   B_history_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:37 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/09 17:13:39 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char	*line;

	while (1)
	{
		line = readline("minishell > ");
		add_history(line);
		free(line);
	}
}

/*
https://linux.die.net/man/3/history

RUN:
gcc B_history_terminal.c -lreadline
./a.out
 */
