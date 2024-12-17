/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:55 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/18 01:01:58 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

# define TO_SPLIT -69

typedef enum e_token_type {
	PIPE,
	COMMAND,
	REDIRECTION,
	COMMAND_FLAG,
	STRING,
}	t_token_type;

typedef struct s_token {
	char			*value;
	t_token_type	*type;
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
