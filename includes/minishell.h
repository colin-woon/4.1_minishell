/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:29:55 by cwoon             #+#    #+#             */
/*   Updated: 2025/02/03 14:42:12 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
# include <sys/stat.h>

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
	SYNTAX_ERROR,
	UNCLOSED_SINGLE_QUOTE,
	UNCLOSED_DOUBLE_QUOTE,
	QUOTE_ERROR,
	MALLOC_ERROR,
	CMD_NOT_EXECUTABLE = 126,
	CMD_NOT_FOUND = 127,
};

enum e_syntax_errors
{
	UNDEFINED,
	PIPE_ERR_SYNTAX,
	NEWLINE_ERR_SYNTAX
};

 # define TOKEN_BUFFER 4096
 # define HEREDOC_FILE "/tmp/.heredoc.txt"
 # define READ_END 0
 # define WRITE_END 1

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
	int		std_fds[2];
}	t_io_fds;

typedef struct s_cmd
{
	char			*name;
	char			*path;
	char			**args;
	int				has_pipe;
	int				pipe_fd[2];
	t_io_fds		*io_fds;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_envp
{
	char			*variable_name;
	char			*value;
	struct s_envp	*prev;
	struct s_envp	*next;
}	t_envp;

typedef struct s_data
{
	t_envp	*our_envp;
	char	**envp_array;
	t_token	*tokens;
	t_cmd	*cmd;
	pid_t	pid;
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
void	print_envp_list(t_envp *head);

// SIGNALS

void	ignore_sigquit();
static void	handle_sigint(int signum);
void	set_signals_input();
void	signal_print_newline(int signal);
void	set_signals_execution();

// MEMORY - Utils Free

void	free_ptr(void *ptr);
void	garbage_collector(t_data *data, char *input, int is_clear_env_cache);
void	close_pipes(t_cmd *cmd, t_cmd *cmd_to_ignore);
void	close_fds(t_cmd *cmd, int is_restore_stdio);
void	exit_process(t_data *data, int exit_status);

// Utils for t_envp doubly linked list

char	*get_our_envp(t_envp *envp, char *variable_name);
t_envp	*create_envp_node(char *var_name, char *value);
void	clear_envp_list(t_envp **head);
void	update_envp_value(t_envp *head, char *var_name, char *new_value);
t_envp	*search_envp(t_envp *head, char *var_name);
void	delete_envp_node(t_envp **head, char *var_name);
void	append_envp(t_envp **head, t_envp *new_node);

// Utils for t_token doubly linked list

t_token	*create_token(char *value, int type);
void	clear_tokens(t_token **head);
void	insert_token_node(t_token *prev_node, t_token *new_node);
void	delete_token(t_token **head, t_token *node_to_delete);
void	append_token(t_token **head, t_token *new_node);

// Utils for t_cmd doubly linked list

t_cmd	*create_cmd();
void	prepend_cmd(t_cmd **head, t_cmd *new_cmd);
void	append_cmd(t_cmd **head, t_cmd *new_cmd);
void	delete_cmd(t_cmd *cmd, void (*del)(void *));
void	clear_cmd_list(t_cmd **head);
t_cmd	*get_last_cmd(t_cmd *cmd);

// Utils for t_io_fds array struct

void	init_io_fds(t_cmd *cmd);
void	free_io_fds(t_io_fds *io_fds);

// ERROR HANDLING

void	print_error(int error_code);
void	print_syntax_error(int syntax_error, char *value);
void	ft_quoted_putendl_fd(char *value, int fd);
void	print_errno_str(char *source, char *value, char *err_no_msg);

// INITIALIZATION

void	init_shell_data(t_data *data, char **envp);
void	init_envp(t_data *data, char **envp);

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

// PARSE INPUT - Utils Parse Token 1 - Validate Syntax

int		validate_syntax(t_token **token);
void	detect_expandable_variable(t_token *token_node);
int		is_consecutive_operator(t_token *token_node);

// PARSE INPUT - Utils Parse Token 2a - Substitute Variable

void		substitute_variable(t_data *data, t_token **token_list);
char		*get_variable(t_token *token, char *var_str, t_data *data);
void		replace_variable(t_token *token_node, char *variable_name, char *variable_result);

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
// PARSE INPUT - COMMANDS - construction

void	construct_commands(t_data *data, t_token *token);

// PARSE INPUT - COMMANDS - 0_parse_word

void	parse_word(t_cmd **cmd, t_token **tokens);
int		fill_cmd_args(t_token **current_tokens, t_cmd *last_cmd);
int		count_args_in_tokens(t_token *token);

// PARSE INPUT - COMMANDS - 1_parse_redirect_in

void	parse_redirect_in(t_cmd **last_cmd, t_token **tokens);
void	open_infile(t_io_fds *io, char *filename);

// PARSE INPUT - COMMANDS - 2_parse_redirect_out

void	open_outfile_truncate(t_io_fds *io, char *filename);
void	parse_redirect_out(t_cmd **last_cmd, t_token **tokens);

// PARSE INPUT - COMMANDS - 3_parse_heredoc

void	parse_heredoc(t_cmd **last_cmd, t_token **tokens);
void	run_heredoc(t_io_fds *io);
int		is_matching_heredoc_limiter(char *input, char *limiter);

// PARSE INPUT - COMMANDS - 4_parse_append

void	parse_append(t_cmd **last_cmd, t_token **tokens);
void	open_outfile_append(t_io_fds *io, char *filename);

// PARSE INPUT - COMMANDS - 5_parse_pipe

void	parse_pipe(t_cmd **cmd, t_token **current_tokens);

// EXECUTION - Execute

void	execute(t_data *data);
int		execute_builtin(t_data *data, t_cmd *cmd);
int		execute_pipes(t_data *data);
void	execute_commands(t_data *data, t_cmd *cmd);
int		execute_binary(t_data *data, t_cmd *cmd);

// EXECUTION - Validation

int	create_pipes(t_data *data);
int	is_valid_files(t_io_fds *io);
int	prepare_commands(t_data *data);

// EXECUTION - Handle_stdios

void	init_stdfds(t_io_fds *io);
void	restore_stdio(t_io_fds *io);
void	redirect_stdio(t_io_fds *io);

// EXECUTION - Utils Pipe Commands

int		get_cmd_path(t_data *data, t_cmd *cmd);
void	setup_pipefds(t_cmd *cmds_list, t_cmd *cmd_to_ignore);
int		is_invalid_command(t_cmd *cmd);
int		wait_cmds(t_data *data);

// EXECUTION - Utils Convert Env
char	**convert_envp(t_data *data, t_envp *envp);

// BUILTINS - CD

int		ft_cd(t_data *data, char **args);
int		change_dir(t_data *data, char *path);

// BUILTINS - PWD

int	ft_pwd(t_data *data, char **args);

// BUILTINS - ENV

int		ft_env(t_data *data, char **args);

// BUILTINS - EXPORT

int	ft_export(t_data *data, char **args);
int	check_valid_env_var(char *env_var);

// BUILTINS - ECHO

int	ft_echo(t_data *data, char **args);

// BUILTINS - UNSET

int	ft_unset(t_data *data, char **args);

// BUILTINS - EXIT

int	ft_exit(t_data *data, int exit_status);
