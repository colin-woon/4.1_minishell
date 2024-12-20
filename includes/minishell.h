/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:55 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/20 18:07:09 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_exit_code;

// # define SPACES " \t\n"
// # define PIPE "|"
// # define HEREDOC "<<"
// # define APPEND ">>"
// # define REDIRECT_IN "<"
// # define REDIRECT_OUT ">"

enum e_token_type
{
	END_OF_FILE = -1,
	NONE,
	SPACES,
	PIPE,
	REDIRECT_IN,
	HEREDOC,
	REDIRECT_OUT,
	APPEND,
};

enum e_error_codes
{
	SUCCESS,
	FAILURE,
	UNCLOSED_SINGLE_QUOTE,
	UNCLOSED_DOUBLE_QUOTE,
	SYNTAX_ERROR
};

enum e_quote_status {
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
};

typedef struct s_token {
	char			*value;
	// t_token_type	*type;
	// t_token	*prev;
	// t_token	*next;
}	t_token;

typedef struct s_command {

}	t_command;

typedef struct s_data {
	char	**envp_array;
	char	**envp_origin;
	int		std_fds[3];
	// char	*readline;
	// t_token	*tokens;
}	t_data;

// INIT
void	init_shell_data(t_data *data, char **envp);
void	init_env(t_data *data, char **envp);
void	init_stdfds(t_data *data);
