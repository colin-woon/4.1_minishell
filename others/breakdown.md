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

Prep for execution
-- IF data.cmd is NULL,
	-SUCCESS
-- IF data.cmd.name is NULL
	-- if data.cmd.iofds &&
			!check_infile_outfile
			{
				-- IF !io OR (!infile && !outfile)
					SUCCESS
				-- infile exist but fd is still -1 OR outfile exist but fd is still -1
					FAILURE
				SUCCESS
			}
		FAILURE
	SUCCESS
- IF
		!create_pipes
		{
			-- LOOP through COMMANDS
				-- IF command has pipe OR previous command has pipe
					- malloc fd int array with size 2
					-- IF (malloc_error OR pipe(fd) error)
						free_data, if pipe error, 129, if malloc_error, mallor_error, RETURN FAILURE
					- assign the fd int array to the cmd pipe_fd
				-next COMMAND
				RETURN SUCCESS
		}
	FAILURE



```
