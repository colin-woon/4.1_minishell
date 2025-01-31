(NFB) = (NEEDS FURTHER BREAKDOWN)

```sh
# Tokenization (DONE)
# - parse into tokens including quotes (" ", ' ')

# Check syntax or grammar (DONE)
# - pipe (|) is not first
# - any expandable variables ($)
# 	- YES
# 		- IF previous is ("<<"), ignore to use as limiter for HEREDOC
# 		- ELSE
# 			- assign token type VAR
# - check for consecutive operators (if yes, its a syntax error)
# 	- double pipe ("||") (can be removed if doing bonus)
# 	- ">>  <<<<  << >>>>"
# 	- '0/'(EOF) with any of these: "|  >  <<  >>  <"

# Expand variable (DONE)
# - Loops through token nodes for VAR type
# - IF FOUND, loops through token value
# 	- updates quote status
# 	- IF
# 		- finds char '$' &&
# 		- next char is not a seperator &&
# 		- quote status is NO_QUOTE or DOUBLE_QUOTE
# 		- THEN expand VAR (NEEDS FURTHER BREAKDOWN)
# 			- get_variable
# 				- identify the variable name (get the start and end of the variable, end should be before any seperators)
# 				- compare with the env
# 				- if found, skip the equal, then extract the value
# 				- if not found, check if its ?, handle by getting exit code of last command.
# 			- substitute_variable
# 				- if get_variable is NULL, remove the variable substring from the string itself
# 					- eg ("hello $fake world") > ("hello  world")
# 				- ELSE
# 					- eg $real=123 ("hello $real world") > ("hello 123 world")

# 	- ELSE
# 		- next char
# - ELSE
# 	- next token

# Handle quotes (DONE)
# - finds quote in token value
# - IF FOUND
# 	- THEN remove quotes (NEEDS FURTHER BREAKDOWN)
# - ELSE
# 	- next token

# Create commands(likely AST?)
```

```sh
CONSTRUCTING COMMANDS

WHILE current temp next is not NULL
	if current temp is same as token (basically init first cmd)
	- append

# 	if type is WORD || VARIABLE
# 	- parse_word
# 		-- LOOP while same types
# 			- get last cmd,
# 			-- IF prev is NULL / prev is PIPE / last_cmd is NULL
# 				-- IF type is VARIABLE and the value got space (is_space)
# 					- split_var_cmd_token (rare usecase) (is detecting if VAR type is "-l -a" after expanding, then split with space as delimiter, so can use as command flags)
# 				-- ELSE
# 					- strdup the token value as cmd name in last cmd
# 				-- NEXT
# 			-- ELSE
# 			 - fill_args
# 			{
# 				-- IF last cmd name is echo
# 					-- IF last cmd no args
# 						- create_args_echo_mode (unsure usecase)
# 						{
# 							- remove empty VARIABLE type tokens after parsing
# 							- count args
# 						}
# 					-- ELSE
# 						- add_args_echo_mode (unsure usecase)
# 				-- ELSE
# 					-- IF last cmd initialized but no args
# 						- create_args_default
# 						{
# 							- count number of args (word or var type) then + 2 then malloc using this to **args (will include the command name as the 1st arg)
# 							- strdup command name to arg[0];
# 							-- LOOP while type is WORD / VARIABLE
# 								- strdup the token value to the args
# 							- NULL terminate the args
# 						}
# 					-- ELSE
# 						- add_args_default (unsure usecase)
# 						{
# 							- count number of args from current token (word or var type)
# 							- get the last index of cmd args;
# 							- copy into a new 2D array
# 						}
# 			 }

# - create_args_default
# - create_args_echo_mode (NFB) (unsure usecase) (only exist because want to join args together) (and removes empty var args)
# Can combine because when doing echo builtin, can just loop args, use string join, then print out

	# elif type is REDIRECT_IN
	# - parse_redirect_in (NFB) (for <, the filename will always appear after <,)
	# {
	# 	- get_last_cmd
	# 	- init_io_fds for the cmd (can use memset to 0, but the fds should initialize it with negative numbers since std_fd 0 is std_in);
	# 	-- open_infile (NFB)
	# 	{
			-- remove_old_file_ref (NFB) (usecase, cat < input1.txt < input2.txt, mutiple redir IN in a row)
	# 		{
	# 			-- IF infile
	# 				IF fd_in not initialized ||
	# 		}
	# 		- save the file name at io.infile
	# 		- if io.infile is NULL, handle error (probably wont happen)
	# 		- if fd-in still at initial state, handle error
	# 	}
	# 	-- IF the temp next next exists, replace temp
	# 	-- ELSE temp next
	# }
	# elif type is REDIRECT_OUT
	# - parse_redirect_out
	# 	-- same as redirect_in but with different file permissions and outfile

	elif type is HEREDOC (NEED TO TEST)
	- parse_heredoc
	{
		- same flow as redirect_in at the start
		- opens a temporary file for heredoc get_heredoc_name for multiple heredocs
		- get_heredoc_limiter
		-- run_heredoc (NFB)
		{
			-- run an infinite loop
				- should SET_SIGNALS
				- if input is same as limiter or NULL detected
					- break loop
				- use a buffer, then keep strjoin for each iteration
			- write the buffer into the file
		}
	}
	# elif type is APPEND
	# - parse_append (NFB)
	# 	-similar flow as parse_redirect_out
	# elif type is PIPE
	# - parse_pipe
	# elif type is END_OF_FILE
	# - break

# then prep_no_arg_commands, some commands like pwd, whoami, will not have any args, but they will only fill in the command name of the t_cmd data struct
```


```sh
EXECUTION

# Prep for execution
# -- IF data.cmd is NULL,
# 	-EXIT
# -- IF data.cmd.name is NULL
# 	-- if data.cmd.iofds &&
# 			!check_infile_outfile
# 			{
# 				-- IF !io OR (!infile && !outfile)
# 					SUCCESS
# 				-- infile exist but fd is still -1 OR outfile exist but fd is still -1
# 					FAILURE
# 				SUCCESS
# 			}
# 		EXIT
# 	EXIT
# - IF
# 		!create_pipes
# 		{
# 			-- LOOP through COMMANDS
# 				-- IF command has pipe OR previous command has pipe
# 					- malloc fd int array with size 2
# 					-- IF (malloc_error OR pipe(fd) error)
# 						free_data, if pipe error, 129, if malloc_error, mallor_error, RETURN FAILURE
# 					- assign the fd int array to the cmd pipe_fd
# 				-next COMMAND
# 				RETURN EXIT
# 		}
# 	EXIT
# RETURN DONT EXIT

# Redirect_io
# -- IF io == NULL
# 	return
# -- init_stdfds as backup
# -- IF fd_in value changed from -1
# 	- dup2 to STDIN
# 		- handle dup2 error incase
# -- IF fd_out value changed from -1
# 	- dup2 to STDOUT
# 		- handle dup2 error incase

Execute Builtin (NFB)

# Restore_io
# -- IF io == NULL
# -- if stdfds is dupped, dup2 to the original stdfds again and close the backup stdfds


# Creating children
# -- LOOP while data.pid is the parent process and cmd is not NULL
# 	- fork and store child process pid in data.pid
# 	- handle error IF -1
# 	-- IF pid is 0, which is the child process,
# 		execute (child process logic) (NFB)
# 		{
# 			-- IF no commmand OR no command name OR is_invalid_files
# 				- exit child process
# 			- set_pipe_fds (NFB)
# 			{
# 				HANDLES THIS KIND OF PIPE (cmd1 | cmd2 | cmd3)
# 				-- IF cmd prev has a pipe output,
# 					- dup2 prev pipe read_end to stdin
# 				-- IF cmd current has a pipe output,
# 					- dup2 prev pipe write_end to stdout
# 				- close_pipefds (close all other pipes except own command pipe)
# 			}
# 			- redirect_stdio
# 			- close_fds
# 			{
# 				- close infile & outfile fd
# 				- close_pipeds (close all this time)
# 			}
# 			-- IF doesnt contain '/', is a relative path OR could be builtin
# 			{
# 				- execute_builtin
# 				- exit shell if all is fine
# 				- execute_sys_bin
# 				{
# 					-- IF command is NULL OR command is directory
# 						- CMD_NOT_FOUND
# 					- get_cmd_path
# 					{
# 						-- IF cmd is NULL
# 						- get the conetents of PATH variable from env, probably need to split with :
# 						- prep the command to an absolute path, / + cmd name, eg: /ls
# 						-- LOOP
# 							- each path in PATH + / + cmd name,
# 							- then check access F_OK X_OK
# 							- IF ok, strdup into cmd.args[0], to be used for execve
# 					}
# 					-- IF command no path
# 						- CMD_NOT_FOUND
# 					-- execve, handle error incase
# 					-- return exit failure if execve unsuccessful
# 				}
# 				- exit shell if all is fine
# 			}
# 			- execute_local_bin
# 			{
# 				- checks again if the command path is executable, since a / is detected,
# 				- then assigns the correct error code if error, return
# 				else
# 				- execve
# 			}
# 			- exit_shell
# 		}
	# - next CMD

# get_children (cleanup processes as parent) (NFB)
# {
# 	- close fds and pipe_fds but dont restore_stdio
# 	- wait for all child processes to finish
# 	- extract the exit code from the child process and use it for the parent process
# 		- 	if (WIFSIGNALED(save_status))
# 			status = 128 + WTERMSIG(save_status);
# 		else if (WIFEXITED(save_status))
# 			status = WEXITSTATUS(save_status);
# 		else
# 			status = save_status;

# 	void	wait_cmds(t_info *info)
# {
# 	int		child_status;
# 	pid_t	killed_child_pid;

# 	killed_child_pid = 0;
# 	while (killed_child_pid != -1)
# 	{
# 		if (killed_child_pid == info->last_pid)
# 			info->exit_code = child_status;
# 		killed_child_pid = wait(&child_status);
# 	}
# }
# }
```

```sh
TO TEST:
- multiple valid < << > >>
	eg: cat < realfile1.txt < realfile2.txt (should show realfile2.txt contents)
- test HEREDOC
- test builtin redirections
```
