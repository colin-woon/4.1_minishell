/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:18 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/09 15:44:16 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char	*line;

	while (1)
	{
		// ft_putstr_fd("minishell > ", 1);
		// line = get_next_line(0);
		line = readline("minishell > ");
	}
}
