/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C1_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:37 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/09 17:14:00 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int main()
{
	char	*line;
	char	*to_echo;

	while (1)
	{
		line = readline("minishell > ");
		add_history(line);
		if (strncmp(line, "echo", 4) == 0)
		{
			if (strlen(line) == strlen("echo"))
				printf("\n");
			else
			{
				to_echo = strchr(line, ' ') + 1;
				if (strncmp(to_echo, "-n", 2) == 0)
				{
					to_echo = strchr(to_echo, ' ') + 1;
					printf("%s", to_echo);
				}
				else
					printf("%s\n", to_echo);

			}
		}
		free(line);
	}
}

/*
Replicating: echo and echo -n

RUN:
gcc C1_builtin_echo.c -lreadline
./a.out

TEST WITH:
echo
echo hello
echo -n hello
 */
