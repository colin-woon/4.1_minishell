/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:24:42 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/04 15:44:27 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int error_code);
void	print_syntax_error(int syntax_error, char *value);
void	ft_quoted_putendl_fd(char *value, int fd);
void	print_errno_str(char *source, char *value, char *err_no_msg);

void	print_error(int error_code)
{
	if (error_code == FAILURE)
		ft_putendl_fd(MSG_FAILURE, 2);
	else if (error_code == UNCLOSED_SINGLE_QUOTE)
		ft_putendl_fd(MSG_UNCLOSED_SINGLE_QUOTE, 2);
	else if (error_code == UNCLOSED_DOUBLE_QUOTE)
		ft_putendl_fd(MSG_UNCLOSED_DOUBLE_QUOTE, 2);
	else if (error_code == QUOTE_ERROR)
		ft_putendl_fd(MSG_EOF_ERROR, 2);
	else if (error_code == MALLOC_ERROR)
		ft_putendl_fd(MSG_MALLOC_ERROR, 2);
	else
		ft_putendl_fd("unknown error", 2);
}

void	print_syntax_error(int syntax_error, char *value)
{
	ft_putstr_fd(MSG_SYNTAX_ERROR, 2);
	if (syntax_error == PIPE_ERR_SYNTAX)
		ft_putendl_fd("`|'", 2);
	else if (syntax_error == NEWLINE_ERR_SYNTAX)
		ft_putendl_fd("`newline'", 2);
	else
		ft_quoted_putendl_fd(value, 2);
}

void	ft_quoted_putendl_fd(char *value, int fd)
{
	ft_putchar_fd('`', fd);
	ft_putstr_fd(value, fd);
	ft_putchar_fd('\'', fd);
	ft_putchar_fd('\n', fd);
}

void	print_errno_str(char *source, char *value, char *err_no_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(source, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (value)
	{
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err_no_msg, STDERR_FILENO);
}
