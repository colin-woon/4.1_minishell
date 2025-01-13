/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:56:26 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/13 19:10:44 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_next_invalid(char next_token_char);
int		is_symbol_only_in_single_quotes(char *token_value, int i_current);
void	remove_substring(char *str, char *substr);
void	replace_substring(char *str, char *substr, char *replacement);
char	*extract_var_without_symbol(char *var_str, int *var_name_len);

int	is_next_invalid(char next_token_char)
{
	if (next_token_char == '$' \
	|| next_token_char == ' ' \
	|| next_token_char == '=' \
	|| next_token_char == '\0')
		return (1);
	else
		return (0);
}

int	is_symbol_only_in_single_quotes(char *token_value, int i_current)
{
	if (i_current > 0)
	{
		if (token_value[i_current - 1] == '\'' \
		&& token_value[i_current + 1] == '\'')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

/*
Find the first occurrence of substr in str
Shift the remaining part of the string
+1 to include null-terminator
 */
void	remove_substring(char *str, char *substr)
{
	char	*substr_pos;
	size_t	len_substr;
	size_t	len_rest;

	substr_pos = ft_strnstr(str, substr, ft_strlen(str));
	if (substr_pos != NULL) {
		len_substr = ft_strlen(substr);
		len_rest = ft_strlen(substr_pos + len_substr);
		ft_memmove(substr_pos, substr_pos + len_substr, len_rest + 1);
	}
}

/*
Function to replace the first occurrence of a substring with another substring
Temporary buffer to hold the modified string
Find the first occurrence of substr in str
Length of the part before the substring
Build the new string in the buffer using strlcpy and strlcat
Copy the part before the substring
Add the replacement
Add the rest of the original string
Copy the result back into the original string using strlcpy
 */
void	replace_substring(char *str, char *substr, char *replacement)
{
	char	buffer[1024];
	char	*pos;
	size_t	len_before;
	size_t	len_substr;
	size_t	len_replacement;

	pos = ft_strnstr(str, substr, ft_strlen(str));
	if (pos != NULL) {
		len_before = pos - str;
		len_substr = ft_strlen(substr);
		len_replacement = ft_strlen(replacement);
		ft_strlcpy(buffer, str, len_before + 1);
		ft_strlcat(buffer, replacement, sizeof(buffer));
		ft_strlcat(buffer, pos + len_substr, sizeof(buffer));
		ft_strlcpy(str, buffer, sizeof(buffer));
	}
}

char	*extract_var_without_symbol(char *var_str, int *var_name_len)
{
	while (var_str[++(*var_name_len)])
	{
		if (is_next_invalid(var_str[(*var_name_len)]))
			break;
	}
	return(ft_substr(var_str, 0, (size_t)(*var_name_len)));
}
