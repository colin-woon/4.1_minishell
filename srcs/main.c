/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/18 01:01:48 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_data(t_data *data, char **envp);
void	init_env(t_data *data, char **envp);

int main(int ac, char **av, char **envp)
{
	t_data	data;
	char	*input;

	((void)ac, (void)av);
	ft_memset(&data, 0, sizeof(t_data));
	init_shell_data(&data, envp);
	while (1)
	{
		input = readline("minishell > ");
		add_history(input);
		// tokenization(&data);
		// printf("%s\n", readline);
		free(input);
	}
}

void	init_shell_data(t_data *data, char **envp)
{
	    int i = 0;

	init_env(data, envp);
    while (data->envp_array[i])
    {
        printf("%s\n", data->envp_array[i]);
        i++;
    }
	// init_stdfds(data);
	// data->envp_origin = envp;
}

void	init_env(t_data *data, char **envp)
{
	int	total_env;
	int	i;

	total_env = 0;
	while (envp && envp[total_env])
		total_env++;
	data->envp_array = ft_calloc(total_env + 1, sizeof(char *));
	if (data->envp_array == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		data->envp_array[i] = ft_strdup(envp[i]);
		if (data->envp_array[i] == NULL)
			return ;
		i++;
	}
}
