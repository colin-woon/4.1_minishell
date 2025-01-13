```sh
Tokenization (DONE)
- parse into tokens including quotes (" ", ' ')

Check syntax or grammar (DONE)
- pipe (|) is not first
- any expandable variables ($)
	- YES
		-- IF previous is ("<<"), ignore to use as limiter for HEREDOC
		-- ELSE
			- assign token type VAR
- check for consecutive operators (if yes, its a syntax error)
	- double pipe ("||") (can be removed if doing bonus)
	- ">>  <<<<  << >>>>"
	- '0/'(EOF) with any of these: "|  >  <<  >>  <"

Expand variable
- Loops through token nodes for VAR type
-- IF FOUND, loops through token value
	- updates quote status
	-- IF
		- finds char '$' &&
		- next char is not a seperator &&
		- quote status is NO_QUOTE or DOUBLE_QUOTE
		-- THEN expand VAR (NEEDS FURTHER BREAKDOWN)
			- get_variable
				- identify the variable name (get the start and end of the variable, end should be before any seperators)
				- compare with the env
				- if found, skip the equal, then extract the value
				- if not found, check if its ?, handle by getting exit code of last command.
			- substitute_variable
				- if get_variable is NULL, remove the variable substring from the string itself
					- eg ("hello $fake world") > ("hello  world")
				-- ELSE
					- eg $real=123 ("hello $real world") > ("hello 123 world")

	-- ELSE
		- next char
-- ELSE
	- next token

Handle quotes
- finds quote in token value
-- IF FOUND
	-- THEN remove quotes (NEEDS FURTHER BREAKDOWN)
-- ELSE
	- next token

Create commands(likely AST?)
```
