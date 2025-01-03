/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/25 19:10:43 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		tokenization(&data, input);
		// printf("%s\n", readline);
		free(input);
		if (ac > 1 && !ft_strncmp(av[1], "-debug", 6))
			break ;
	}
}
