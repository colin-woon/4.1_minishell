/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/13 21:53:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	((void)ac, (void)av);
	ft_memset(&data, 0, sizeof(t_data));
	init_shell_data(&data, envp);
	while (1)
	{
		if (ac > 1 && !ft_strncmp(av[1], "-debug", 6))
			input = ft_strdup(av[2]);
		else
			input = readline("minishell > ");
		add_history(input);
		parse_input(&data, input);
		garbage_collector(&data, input);
		if (ac > 1 && !ft_strncmp(av[1], "-debug", 6))
			break ;
	}
}
