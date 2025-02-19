# DEBUG FORMAT:
# ../minishell -debug "<input-command>"
# best to use double quotes to ignore spaces as seperate commands, will need to use \ if want to include double quotes

RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
ORANGE='\033[38;5;214m'
BLUE='\033[34m'
END='\033[0m'

MAKEFILE_DIR="../"
MINISHELL_EXEC="../minishell"

make -C "$MAKEFILE_DIR"
echo

# # TOKENIZATION
# # PRINT TOKENS
# echo "${GREEN}USE PRINT TOKENS TO CHECK${END}"
# echo "${YELLOW}NORMAL COMMAND${END}"
# ../minishell -debug "echo \"hello world\""
# echo

# echo "${BLUE}DISABLE parse_tokens IN parse_input.c OR ELSE WILL ERROR${END}"
# echo "${YELLOW}DETECTING SEPARATORS${END}"
# ../minishell -debug "hi | < << > >>"
# echo

# echo "${YELLOW}MULTIPLE DOUBLE QUOTES${END}"
# ../minishell -debug "\"hi | <\" << > >>\"\""
# echo

# echo "${YELLOW}MULTIPLE SINGLE QUOTES${END}"
# ../minishell -debug "''''"
# echo

# # ERROR
# echo "${RED}SHOULD BE ERRORS${END}"
# echo "${ORANGE}UNCLOSED DOUBLE QUOTE${END}"
# ../minishell -debug "\"hi | < << > >>\"\""
# echo

# echo "${ORANGE}UNCLOSED SINGLE QUOTE${END}"
# ../minishell -debug "'''"
# echo

# # ASSIGNING EXPANDABLE VARIABLE TYPE
# # PRINT TOKENS
# echo "${GREEN}USE PRINT TOKENS TO CHECK${END}"
# echo "${YELLOW}DETECTING VAR TYPE${END}"
# ../minishell -debug "hello \$PAR"
# echo

# # ERROR
# echo "${RED}SHOULD BE ERRORS${END}"
# ../minishell -debug "|"
# ../minishell -debug "<"
# ../minishell -debug "<<"
# ../minishell -debug ">"
# ../minishell -debug ">>"
# ../minishell -debug "asd |"
# ../minishell -debug "asd <"
# ../minishell -debug "asd <<"
# ../minishell -debug "asd >"
# ../minishell -debug "asd >>"

# echo "${RED}SHOULDNT SUBSTITUTE${END}"
# ../minishell -debug "echo 'hello '$' world'"
# echo

# echo "${GREEN}SHOULD SUBSTITUTE${END}"
# echo "${BLUE}First${END}"
# ../minishell -debug "echo hello \"\$fake\" world"
# echo "${BLUE}Second${END}"
# ../minishell -debug "echo hello \"\$\" world"
# echo

../minishell -debug "echo \"hello \$world asd\""
echo
../minishell -debug "echo \"hello \$PAGER asd\""
echo
../minishell -debug "echo \"hello \$WSL asd\""
echo
../minishell -debug "echo \"hello \$WSLENV asd\""

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1

# 4.1_minishell [main●] echo $PAGER
# less
# 4.1_minishell [main●] echo '$PAGER'
# $PAGER
# 4.1_minishell [main●] echo "$PAGER"
# less
# 4.1_minishell [main●] echo "hello $PAGER"
# hello less
# 4.1_minishell [main●] echo "hello '$PAGER'"
# hello 'less'
# 4.1_minishell [main●] echo "hello "$PAGER""
# hello less
# 4.1_minishell [main●] echo "hello" "$PAGER"
# hello less

# ~/42_core_program/4.1_minishell (main)*$ cat << abc
# > echo $PAGER
# > abc
# echo less
