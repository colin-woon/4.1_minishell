/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:55 by cwoon             #+#    #+#             */
/*   Updated: 2025/01/22 18:55:09 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_last_exit_code;

enum e_token_type
{
	END_OF_FILE = -1,
	NONE,
	SPACES,
	WORD,
	VARIABLE,
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
	QUOTE_ERROR,
	MALLOC_ERROR
};

enum e_syntax_errors
{
	UNDEFINED,
	PIPE_ERR_SYNTAX,
	NEWLINE_ERR_SYNTAX
};

 # define TOKEN_BUFFER 4096
 # define MSG_FAILURE "error"
 # define MSG_UNCLOSED_SINGLE_QUOTE "minishell: unexpected EOF while looking for matching '"
 # define MSG_UNCLOSED_DOUBLE_QUOTE "minishell: unexpected EOF while looking for matching \""
 # define MSG_EOF_ERROR "minishell: unexpected end of file"
 # define MSG_SYNTAX_ERROR "minishell: syntax error near unexpected token "
 # define MSG_MALLOC_ERROR "malloc error"

enum e_quote_status
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
};

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_limiter;
	int		is_heredoc_quotes;
	int		fd_in;
	int		fd_out;
}	t_io_fds;

typedef struct s_cmd
{
	char			*name;
	char			*path;
	char			**args;
	int				has_pipe;
	int				*pipe_fd;
	t_io_fds		*io_fds;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	**envp_array;
	char	**envp_origin;
	int		std_fds[3];
	t_token	*tokens;
	t_cmd	*cmd;
}	t_data;

// DEBUG - Printing

void	print_tokens(t_token *tokens);
void	print_envp_array(t_data *data);
void	print_value_str(char *message, char *value);
void	print_value_int(char *message, int value);
void	print_value_char(char *message, char value);
void	print_cmd(t_cmd *cmd);
void	print_all_cmds(t_cmd *head);
void	print_io_fds(t_io_fds *io_fds);

// MEMORY - Utils Free

void	free_ptr(void *ptr);
void	garbage_collector(t_data *data, char *input);

// ERROR HANDLING

void	print_error(int error_code);
void	print_syntax_error(int syntax_error, char *value);
void	ft_quoted_putendl_fd(char *value, int fd);

// INITIALIZATION

void	init_shell_data(t_data *data, char **envp);
void	init_env(t_data *data, char **envp);
void	init_stdfds(t_data *data);

// PARSE INPUT

int		parse_input(t_data *data, char *input);

// PARSE INPUT - TOKENIZATION

int		tokenization(t_data *data, char *input);
int		save_word_or_seperator(int *i_current, char *input, int from, t_data *data);
void	save_word(int from, char *input, int i_current, t_token **tokens);
void	save_seperator(int i_current, int type, char *input, t_token **tokens);

// PARSE INPUT - TOKENIZATION - Utils Tokenization

int		get_seperator(char *input, int i_current);
int		check_quote(int	is_quote, char *input, int i_current);

// PARSE INPUT - TOKENIZATION - Utils for t_token doubly linked list

t_token	*create_token(char *value, int type);
void	clear_tokens(t_token **head);
void	insert_token_node(t_token *prev_node, t_token *new_node);
void	delete_token(t_token **head, t_token *node_to_delete);
void	append_token(t_token **head, t_token *new_node);

// PARSE INPUT - Utils Parse Token 1 - Validate Syntax

int		validate_syntax(t_token **token);
void	detect_expandable_variable(t_token *token_node);
int		is_consecutive_operator(t_token *token_node);

// PARSE INPUT - Utils Parse Token 2a - Substitute Variable

void		substitute_variable(t_data *data, t_token **token_list);
char		*get_variable(t_token *token, char *var_str, t_data *data);
void		replace_variable(t_token *token_node, char *variable_name, char *variable_result);
static void	clean_up(char *extracted_var, char *var_w_equal_sign);

// PARSE INPUT - Utils Parse Token 2b - Helper Functions

int		is_next_invalid(char next_token_char);
int		is_symbol_only_in_single_quotes(char *token_value, int i_current);
void	remove_substring(char *str, char *substr);
char	*replace_substring(char *str, char *substr, char *replacement);
char	*extract_var_without_symbol(char *var_str, int *var_name_len);

// PARSE INPUT - Utils Parse Token 3 - Handle Quotes

void	handle_quotes(t_token **token_list);
void	remove_all_quotes(char *value, int is_quote_old, int *i);

// PARSE INPUT - COMMANDS
// PARSE INPUT - COMMANDS - utils_t_cmd

t_cmd	*create_cmd();
void	prepend_cmd(t_cmd **head, t_cmd *new_cmd);
void	append_cmd(t_cmd **head, t_cmd *new_cmd);
void	delete_cmd(t_cmd **head, t_cmd *cmd_to_delete);
void	clear_cmd_list(t_cmd **head);
t_cmd	*get_last_cmd(t_cmd *cmd);

// PARSE INPUT - COMMANDS - utils_t_io_fds

t_io_fds	*create_io_fds(char *infile, char *outfile, char *heredoc_limiter, int is_heredoc_quotes);
void	free_io_fds(t_io_fds *io_fds);
