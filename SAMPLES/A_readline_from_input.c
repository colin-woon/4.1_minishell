/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_readline_from_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:37 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/09 17:13:43 by cwoon            ###   ########.fr       */
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
		printf("%s\n", line);
		free(line);
	}
}

/*
https://www.man7.org/linux/man-pages/man3/readline.3.html

RUN:
gcc A_readline_from_input.c -lreadline
./a.out
 */
