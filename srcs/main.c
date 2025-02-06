/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/06 14:35:30 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc_sigint;

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	((void)ac, (void)av);
	ft_memset(&data, 0, sizeof(t_data));
	init_shell_data(&data, envp);
	while (1)
	{
		set_signals_input();
		if (ac > 1 && !ft_strncmp(av[1], "-debug", 6))
			input = ft_strdup(av[2]);
		else
			input = readline("minishell > ");
		set_signals_execution();
		if (parse_input(&data, input) == SUCCESS)
			execute(&data);
		if (ac > 1 && !ft_strncmp(av[1], "-debug", 6))
		{
			garbage_collector(&data, input, true);
			break ;
		}
		else
			garbage_collector(&data, input, false);
	}
}
