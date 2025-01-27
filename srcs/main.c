/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/27 15:35:12 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

void	execute_commands(t_data *data);
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
		if (parse_input(&data, input) == SUCCESS)
			execute_commands(&data);
		garbage_collector(&data, input);
		if (ac > 1 && !ft_strncmp(av[1], "-debug", 6))
			break ;
	}
}

void	execute_commands(t_data *data)
{
	int	is_exit;

	is_exit = validate_commands(data);
	if (is_exit)
		return ;
	// if (!data->cmd->has_pipe && !data->cmd->prev && is_valid_files(data->cmd->io_fds))
	// {
	// 	redirect_io
	// 	execute_builtin
	// 	restore_io
	// }
	if (is_exit)
		return ;
	// return (create_children(data));
}
