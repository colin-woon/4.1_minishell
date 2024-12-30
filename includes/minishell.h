/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:55 by cwoon             #+#    #+#             */
/*   Updated: 2024/12/30 19:01:38 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_last_exit_code;

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
	WORD,
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
	SYNTAX_ERROR,
	MALLOC_ERROR
};

 # define MSG_FAILURE "error"
 # define MSG_UNCLOSED_SINGLE_QUOTE "unexpected EOF while looking for matching '"
 # define MSG_UNCLOSED_DOUBLE_QUOTE "unexpected EOF while looking for matching \""
 # define MSG_SYNTAX_ERROR "syntax error: unexpected end of file"
 # define MSG_MALLOC_ERROR "malloc error"

enum e_quote_status {
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
};

typedef struct s_token {
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_command {

}	t_command;

typedef struct s_data {
	char	**envp_array;
	char	**envp_origin;
	int		std_fds[3];
	t_token	*tokens;
}	t_data;

// Print Debug

void	print_tokens(t_token *tokens);
void	print_envp_array(t_data *data);

// Utils Free

void	free_ptr(void *ptr);
void	garbage_collector(t_data *data, char *input);

// Error

void	print_error(int error_code);

// Init

void	init_shell_data(t_data *data, char **envp);
void	init_env(t_data *data, char **envp);
void	init_stdfds(t_data *data);

// Parse Input

int	parse_input(t_data *data, char *input);

// Tokenization

int		save_word_or_seperator(int *i_current, char *input, int from, t_data *data);
int		get_seperator(char *input, int i_current);
int		tokenization(t_data *data, char *input);
int		check_quote(int	is_quote, char *input, int i);
void	save_word(int from, char *input, int i_current, t_token **tokens);
void	save_seperator(int i_current, int type, char *input, t_token **tokens);

// Tokenization - Utils for t_token doubly linked list

t_token	*create_token(char *value, int type);
void	clear_tokens(t_token **head);
void	insert_token_node(t_token *prev_node, t_token *new_node);
void	delete_token(t_token **head, t_token *node_to_delete);
void	append_token(t_token **head, t_token *new_node);
