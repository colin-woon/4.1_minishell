```sh
Tokenization
- parse into tokens including quotes (" ", ' ')

Check syntax or grammar
- pipe (|) is not first
- any expandable variables ($)
	- YES
		-- IF previous is (<<), ignore to use as limiter for HEREDOC
		-- ELSE
			- assign token type VAR
- check for consecutive operators (if yes, its a syntax error)
	- double pipe (||) (can be removed if doing bonus)
	- >>  <<<<  << >>>>
	- '0/'(EOF) with any of these: |  >  <<  >>  <

Expand variable
- Loops through token nodes for VAR type
-- IF FOUND, loops through token value
	- updates quote status
	-- IF
		- finds char '$' &&
		- next char is not a seperator &&
		- quote status is NO_QUOTE or DOUBLE_QUOTE
		-- THEN expand VAR (NEEDS FURTHER BREAKDOWN)
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
