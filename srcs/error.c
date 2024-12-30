/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:24:42 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/30 19:02:09 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error_code);

void	print_error(int error_code)
{
	if (error_code == FAILURE)
		ft_putendl_fd(MSG_FAILURE, 2);
	else if (error_code == UNCLOSED_SINGLE_QUOTE)
		ft_putendl_fd(MSG_UNCLOSED_SINGLE_QUOTE, 2);
	else if (error_code == UNCLOSED_DOUBLE_QUOTE)
		ft_putendl_fd(MSG_UNCLOSED_DOUBLE_QUOTE, 2);
	else if (error_code == SYNTAX_ERROR)
		ft_putendl_fd(MSG_SYNTAX_ERROR, 2);
	else if (error_code == MALLOC_ERROR)
		ft_putendl_fd(MSG_MALLOC_ERROR, 2);
	else
		ft_putendl_fd("unknown error", 2);
}
