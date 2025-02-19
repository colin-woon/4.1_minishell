/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_token_2b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:56:26 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/17 19:19:31 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_next_invalid(char next_token_char, int comparing_with_symbol_before);
int		is_symbol_only_in_quotes(char *token_value, int i_current);
void	remove_substring(char *str, char *substr);
char	*replace_substring(char *str, char *substr, char *replacement);
char	*extract_var(char *var_str);

/*
$$ (supposed to expand to PID of current shell in bash)
not supposed to substitute:
- $<NULL>
- $<SPACE>
- $=
- $$
- $USER.txt (only substitute the USER part)

$_ is accepted
 */
int	is_next_invalid(char next_token_char, int comparing_with_symbol_before)
{
	int	is_invalid;

	is_invalid = 0;
	if (next_token_char == '$' \
	|| next_token_char == ' ' \
	|| next_token_char == '=' \
	|| next_token_char == '\0' \
	|| (next_token_char != '_' \
	&& !ft_isalnum(next_token_char)))
		is_invalid = 1;
	if (comparing_with_symbol_before)
	{
		if (next_token_char == '?')
			is_invalid = 0;
	}
	return (is_invalid);
}

/*
refers to '$' || "$"
 */
int	is_symbol_only_in_quotes(char *token_value, int i_current)
{
	if (i_current > 0)
	{
		if ((token_value[i_current - 1] == '\'' && \
		token_value[i_current + 1] == '\'') \
		|| (token_value[i_current - 1] == '\"' && \
		token_value[i_current + 1] == '\"'))
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
	if (substr_pos != NULL)
	{
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
 */
char	*replace_substring(char *str, char *substr, char *replacement)
{
	char	buffer[TOKEN_BUFFER];
	char	*pos;
	size_t	len_before;
	size_t	len_substr;

	pos = ft_strnstr(str, substr, ft_strlen(str));
	if (pos)
	{
		len_before = pos - str;
		len_substr = ft_strlen(substr);
		ft_strlcpy(buffer, str, len_before + 1);
		ft_strlcat(buffer, replacement, sizeof(buffer));
		ft_strlcat(buffer, pos + len_substr, sizeof(buffer));
		free_ptr((void **)&str);
		return (ft_strdup(buffer));
	}
	else
		return (str);
}

/*
eg: $USER

always returns $USER unless its $?, then return $?
 */
char	*extract_var(char *var_str)
{
	int	i;

	i = 0;
	if (!ft_strncmp(var_str, "$?", 2))
		return (ft_substr(var_str, 0, (size_t)i + 2));
	i++;
	while (var_str[i])
	{
		if (is_next_invalid(var_str[i], false) \
		|| var_str[i] == '\'')
			break ;
		i++;
	}
	if (i != 0)
	{
		if (var_str[i - 1] == '"')
			i--;
	}
	return (ft_substr(var_str, 0, (size_t)i));
}
