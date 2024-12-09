/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   D_ctrl+c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:37 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/09 17:13:19 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int main()
{
	char	*line;

	signal(SIGINT, handle_sigint);
	while (1)
	{
		line = readline("minishell > ");
		if (strncmp(line, "exit", 4) == 0)
		{
			free(line);
			exit(0);
		}
		free(line);
	}
}

/*
RUN:
gcc D_ctrl+c.c -lreadline
./a.out

TEST:
press ctrl+c on keyboard, should go to newline with ^c
then type exit and enter
 */
